#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    qDebug()<<"int main(...) begins";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
