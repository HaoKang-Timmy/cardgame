#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectnumplayer.h"
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

