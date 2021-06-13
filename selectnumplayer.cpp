#include "selectnumplayer.h"
#include "ui_selectnumplayer.h"
#include "_21_points.h"
#include "mainwindow.h"


selectNumPlayer::selectNumPlayer(QWidget *parent, TYPEGAMES type) :
    QMainWindow(parent),
    ui(new Ui::selectNumPlayer)
{
    ui->setupUi(this);
    typeGame = type;
    switch (type) {
        case _21_POINTS:
        setWindowTitle("21点");
        break;
    }
    setWindowFlags(this->windowFlags()& ~Qt::WindowCloseButtonHint);
    ui->lineEdit->setText("Player1");
    ui->lineEdit_2->setText("Player2");
    ui->lineEdit_3->setText("Player3");
    ui->lineEdit_5->setText("Player4");
    ui->comboBox->setCurrentIndex(2);
}

selectNumPlayer::~selectNumPlayer()
{
    delete ui;
}

void selectNumPlayer::on_pushButton_clicked()
{
    switch (ui->comboBox->currentIndex()) {
    case 0: //其实对应的是2，后面以此类推
        if(typeGame == _21_POINTS)
        {
            _21_points *twentyone = new _21_points(nullptr, 2);
            twentyone->setPlayers(ui->lineEdit->text(), ui->lineEdit_2->text());
            this->close();
            twentyone->show();
        }
        break;
    case 1:
        if(typeGame == _21_POINTS)
        {
            _21_points *twentyone = new _21_points(nullptr, 3);
            twentyone->setPlayers(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());
            this->close();
            twentyone->show();
        }
        break;
    case 2:
        if(typeGame == _21_POINTS)
        {
            _21_points *twentyone = new _21_points(nullptr, 4);
            twentyone->setPlayers(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_5->text());
            this->close();
            twentyone->show();
        }
        break;
    }
    this->~selectNumPlayer();
}


void selectNumPlayer::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->lineEdit_3->setDisabled(true);
    case 1:
        ui->lineEdit_5->setDisabled(true);
        break;
    default:
        ui->lineEdit_3->setDisabled(false);
        ui->lineEdit_5->setDisabled(false);
    }
}

void selectNumPlayer::on_pushButton_2_clicked()
{
    w1->setHidden(false);
}

