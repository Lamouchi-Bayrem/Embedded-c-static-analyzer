#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "analysiscontroller.h"
#include <QMainWindow>
#include <QVector>
class QCheckBox; class QComboBox; class QLabel; class QLineEdit; class QPlainTextEdit;
class QProgressBar; class QPushButton; class QTableWidget; class QTreeWidget; class QTabWidget;
class MainWindow final : public QMainWindow {
    Q_OBJECT
public: explicit MainWindow(QWidget *parent=nullptr);
private:
    AnalysisController controller; QVector<Finding> findings;
    QLineEdit *projectEdit{}, *searchEdit{}; QComboBox *standardBox{}, *severityBox{};
    QCheckBox *compilerBox{}, *cppcheckBox{}, *clangTidyBox{}; QLabel *summaryLabel{}, *toolsLabel{};
    QTreeWidget *filesTree{}; QTableWidget *findingsTable{}; QPlainTextEdit *sourceView{}, *detailsView{}, *console{};
    QProgressBar *progress{}; QPushButton *runButton{}, *cancelButton{}, *reportButton{}; QTabWidget *tabs{};
    void buildUi(); void chooseProject(); void scanProject(); QStringList selectedFiles() const;
    QStringList includePaths() const; void detectTools(); void addFinding(const Finding &f);
    void refreshFindings(); void showFinding(int row); void runAnalysis(); void generateReports();
    void updateSummary();
};
#endif
