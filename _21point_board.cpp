#include "_21point_board.h"
#include "ui__21point_board.h"

_21point_Board::_21point_Board(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::_21point_Board)
{
    ui->setupUi(this);
    setWindowTitle("Result");
    labels[0] = ui->label_4;
    labels[1] = ui->label_2;
    labels[2] = ui->label_3;
    labels[3] = ui->label_5;
    labels[4] = ui->label_6;
}

_21point_Board::~_21point_Board()
{
    delete ui;
}

void _21point_Board::on_pushButton_clicked()
{
    w1->setHidden(false);
    accept();
    parent()->~QObject();
}

