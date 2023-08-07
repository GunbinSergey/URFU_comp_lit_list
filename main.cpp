#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int returncode = a.exec();
    if (returncode == -1)
    {
      QProcess* proc = new QProcess();
      proc->start(QCoreApplication::applicationFilePath());
      //QApplication::quit();
    }

    //return a.exec();
}
