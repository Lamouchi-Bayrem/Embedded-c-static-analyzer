#include "mainwindow.h"
#include <QApplication>
int main(int argc,char **argv){ QApplication app(argc,argv);app.setApplicationName("Embedded C Static Analyzer");app.setOrganizationName("Lamouchi-Bayrem");MainWindow window;window.show();return app.exec(); }
