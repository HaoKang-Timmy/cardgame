#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectnumplayer.h"
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("微软雅黑");
    font.setBold(true);
    font.setPointSize(36);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    selectNumPlayer *snp = new selectNumPlayer(nullptr, _21_POINTS);
    snp->show();
    this->close();
    this->~MainWindow();
}

