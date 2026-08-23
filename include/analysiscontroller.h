#ifndef ANALYSISCONTROLLER_H
#define ANALYSISCONTROLLER_H
#include "finding.h"
#include <QObject>
#include <QProcess>
#include <QQueue>
struct AnalysisJob { QString engine; QString program; QStringList arguments; QString workingDirectory; };
class AnalysisController final : public QObject {
    Q_OBJECT
public:
    explicit AnalysisController(QObject *parent=nullptr);
    void start(const QString &project, const QStringList &files, const QString &standard,
               const QStringList &includes, bool compiler, bool cppcheck, bool clangTidy);
    void cancel(); bool isRunning() const;
signals:
    void logMessage(const QString &text); void findingReady(const Finding &finding);
    void progressChanged(int value); void finished(bool cancelled);
private:
    QQueue<AnalysisJob> jobs; QProcess *process{}; int totalJobs{0}; bool cancelled{false};
    void runNext(); void parseOutput(const QString &engine,const QString &text);
};
#endif
