#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
MainWindow *w1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontID=QFontDatabase::addApplicationFont(":/fonts/graph/fonts/msyhbd.ttc");
    QString MSYH=QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont font(MSYH);
    QApplication::setFont(font);
    MainWindow *w = new MainWindow;
    w1 = w;
    w->show();
    return a.exec();
}
