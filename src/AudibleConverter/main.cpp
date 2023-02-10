#include "mainwindow.h"
#include <stdio.h>
#include <QApplication>
#include "Settings.h"
int main(int argc, char *argv[])
{
#ifdef __APPLE__
    chdir(get_executable_dir().c_str());
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
