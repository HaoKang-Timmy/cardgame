#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectnumplayer.h"
#include <QFontDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int fontID = QFontDatabase::addApplicationFont(":/fonts/graph/fonts/Chalkboard-SE-2.ttf");
    QString Chalkboard=QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont font(Chalkboard, 80, QFont::Bold);
    ui->label->setFont(font);
    setWindowTitle("Card Game");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    selectNumPlayer *snp = new selectNumPlayer(nullptr, _21_POINTS);
    snp->show();
    this->setHidden(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    this->~MainWindow();
}

