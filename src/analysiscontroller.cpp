#include "analysiscontroller.h"
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
#include <QStandardPaths>
AnalysisController::AnalysisController(QObject *parent):QObject(parent){}
bool AnalysisController::isRunning() const{return process!=nullptr;}
void AnalysisController::cancel(){cancelled=true;jobs.clear();if(process!=nullptr){process->kill();}}
void AnalysisController::start(const QString &project,const QStringList &files,const QString &standard,const QStringList &includes,bool compiler,bool cppcheck,bool clangTidy){
 if(isRunning())return;jobs.clear();cancelled=false;QStringList includeArgs;for(const QString &i:includes)includeArgs<<"-I"+i;
 const QString cc=!QStandardPaths::findExecutable("clang").isEmpty()?"clang":"gcc";
 for(const QString &file:files){
  if(compiler&&!QStandardPaths::findExecutable(cc).isEmpty()){QStringList a={"-std="+standard,"-Wall","-Wextra","-Wpedantic","-Wconversion","-Wsign-conversion","-Wshadow","-Wundef","-Wformat=2","-Wcast-align","-Wcast-qual","-Wstrict-prototypes","-Wmissing-prototypes","-Wswitch-enum","-Wdouble-promotion","-fsyntax-only"};a<<includeArgs<<file;jobs.enqueue({"Compiler",cc,a,project});}
  if(clangTidy&&!QStandardPaths::findExecutable("clang-tidy").isEmpty()){QStringList a={file,"--checks=clang-analyzer-*,bugprone-*,cert-*,performance-*,portability-*","--","-std="+standard};a<<includeArgs;jobs.enqueue({"Clang-Tidy","clang-tidy",a,project});}
 }
 if(cppcheck&&!QStandardPaths::findExecutable("cppcheck").isEmpty()){QStringList a={"--std="+standard,"--enable=warning,style,performance,portability","--inline-suppr","--suppress=missingIncludeSystem","--template={file}:{line}:{column}: {severity}: [{id}] {message}"};for(const QString &i:includes)a<<"-I"+i;a<<files;jobs.enqueue({"Cppcheck","cppcheck",a,project});}
 totalJobs=jobs.size();if(totalJobs==0){emit logMessage("No available analysis engine was selected.\n");emit progressChanged(100);emit finished(false);return;}emit progressChanged(0);runNext();
}
void AnalysisController::runNext(){
 if(cancelled||jobs.isEmpty()){process=nullptr;emit progressChanged(100);emit finished(cancelled);return;}
 const AnalysisJob job=jobs.dequeue();process=new QProcess(this);process->setWorkingDirectory(job.workingDirectory);process->setProcessChannelMode(QProcess::MergedChannels);
 emit logMessage("\n$ "+job.program+" "+job.arguments.join(' ')+"\n");
 connect(process,&QProcess::readyReadStandardOutput,this,[this]{emit logMessage(QString::fromUtf8(process->readAllStandardOutput()));});
 connect(process,qOverload<int,QProcess::ExitStatus>(&QProcess::finished),this,[this,job](int code,QProcess::ExitStatus){const QString out=QString::fromUtf8(process->readAllStandardOutput());if(!out.isEmpty())emit logMessage(out);parseOutput(job.engine,out);if(code!=0&&out.trimmed().isEmpty()){Finding f;f.severity="Error";f.engine=job.engine;f.rule="ENGINE";f.message="Analyzer exited with code "+QString::number(code);emit findingReady(f);}process->deleteLater();process=nullptr;emit progressChanged(totalJobs==0?100:((totalJobs-jobs.size())*100/totalJobs));runNext();});
 process->start(job.program,job.arguments);if(!process->waitForStarted(2000)){Finding f;f.severity="Error";f.engine=job.engine;f.rule="START";f.message="Could not start "+job.program;emit findingReady(f);process->deleteLater();process=nullptr;runNext();}
}
void AnalysisController::parseOutput(const QString &engine,const QString &text){
 static const QRegularExpression rx(R"(^(.+?):(\d+):(\d+):\s*(fatal error|error|warning|style|performance|portability|information|note):\s*(?:\[([^\]]+)\]\s*)?(.*)$)");
 const QStringList lines=text.split('\n',Qt::SkipEmptyParts);for(const QString &line:lines){auto m=rx.match(line.trimmed());if(!m.hasMatch())continue;Finding f;f.file=QDir::cleanPath(m.captured(1));f.line=m.captured(2).toInt();f.column=m.captured(3).toInt();QString sev=m.captured(4).toLower();f.severity=(sev.contains("error"))?"Error":(sev=="warning"?"Warning":"Review");f.engine=engine;f.rule=m.captured(5).isEmpty()?engine.toUpper():m.captured(5);f.message=m.captured(6);emit findingReady(f);}
}
