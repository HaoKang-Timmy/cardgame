#include "mainwindow.h"

#include <QApplication>

MainWindow *w1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w1 = w;
    w->show();
    return a.exec();
}
