#include "_21_points.h"
#include "ui__21_points.h"
#include "_21point_board.h"

_21_points::_21_points(QWidget *parent, int numPlayers) :
    QMainWindow(parent),
    ui(new Ui::_21_points)
{
    ui->setupUi(this);
    playerNumber = numPlayers;
    init_interface();
    current_player = 0;
    array_player[0].set_round(1);
    ui->label_56->setHidden(true);
    ui->label_57->setHidden(true);
    ui->label_58->setHidden(true);
    setWindowTitle("21点");
}

_21_points::~_21_points()
{
    delete ui;
}

void _21_points::setPlayers(const QString &p1, const QString &p2, const QString &p3, const QString &p4)
{
    array_player[0].set_name(p1);
    array_player[1].set_name(p2);
    array_player[2].set_name(p3);
    array_player[3].set_name(p4);
    ui->label_47->setText(array_player[0].get_name());
    ui->label_51->setText(array_player[1].get_name());
    ui->label_53->setText(array_player[2].get_name());
    ui->label_49->setText(array_player[3].get_name());
}

void _21_points::setCurrentPlayer(int k)
{
    array_player[current_player].set_round(0);
    current_player = k;
    array_player[k].set_round(1);
    ui->label_55->setHidden(true);
    ui->label_56->setHidden(true);
    ui->label_57->setHidden(true);
    ui->label_58->setHidden(true);
    switch (k) {
    case 0:
        ui->label_55->setHidden(false);
        break;
    case 1:
        ui->label_56->setHidden(false);
        break;
    case 2:
        ui->label_57->setHidden(false);
        break;
    case 3:
        ui->label_58->setHidden(false);
    }
}
void _21_points::init_interface()
{
    player_card[0][0] = ui->label_3;
    player_card[0][1] = ui->label_4;
    player_card[0][2] = ui->label_5;
    player_card[0][3] = ui->label_6;
    player_card[0][4] = ui->label_7;
    player_card[0][5] = ui->label_8;
    player_card[0][6] = ui->label_9;
    player_card[0][7] = ui->label_10;
    player_card[0][8] = ui->label_11;
    player_card[0][9] = ui->label_12;
    player_card[0][10] = ui->label_13;
    player_card[1][0] = ui->label_25;
    player_card[1][1] = ui->label_26;
    player_card[1][2] = ui->label_27;
    player_card[1][3] = ui->label_28;
    player_card[1][4] = ui->label_29;
    player_card[1][5] = ui->label_30;
    player_card[1][6] = ui->label_31;
    player_card[1][7] = ui->label_32;
    player_card[1][8] = ui->label_33;
    player_card[1][9] = ui->label_34;
    player_card[1][10] = ui->label_35;
    player_card[2][0] = ui->label_14;
    player_card[2][1] = ui->label_15;
    player_card[2][2] = ui->label_16;
    player_card[2][3] = ui->label_17;
    player_card[2][4] = ui->label_18;
    player_card[2][5] = ui->label_19;
    player_card[2][6] = ui->label_20;
    player_card[2][7] = ui->label_21;
    player_card[2][8] = ui->label_22;
    player_card[2][9] = ui->label_23;
    player_card[2][10] = ui->label_24;
    player_card[3][0] = ui->label_36;
    player_card[3][1] = ui->label_37;
    player_card[3][2] = ui->label_38;
    player_card[3][3] = ui->label_39;
    player_card[3][4] = ui->label_40;
    player_card[3][5] = ui->label_41;
    player_card[3][6] = ui->label_42;
    player_card[3][7] = ui->label_43;
    player_card[3][8] = ui->label_44;
    player_card[3][9] = ui->label_45;
    player_card[3][10] = ui->label_46;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 11; j++)
            player_card[i][j]->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    }

    if(playerNumber == 3 || playerNumber == 2)
    {
        ui->label_49->setHidden(true);
        ui->label_50->setHidden(true);
    }
    if(playerNumber == 2)
    {
        ui->label_53->setHidden(true);
        ui->label_54->setHidden(true);
    }
}


void _21_points::on_pushButton_clicked()//抽牌
{
    qDebug()<<current_player;
    if(playing_heap.isEmpty())
        playing_heap.initRandom(false);
    card got = playing_heap.fetchCard();
    array_player[current_player].player_fetchCard(got);
    if(current_player == 0 || current_player == 2)
    {
        qDebug()<<array_player[current_player].get_num_cards();
        player_card[current_player][array_player[current_player].get_num_cards()-1]->setStyleSheet("background-image: url(" + got.getPicPath() + ");");
    }
    else
    {
        QPixmap pix;
        pix.load(got.getPicPath());
        QTransform trans;
        trans.rotate(90);
        player_card[current_player][array_player[current_player].get_num_cards()-1]->setPixmap(pix.transformed(trans,Qt::SmoothTransformation));
    }
    QString display = "当前点数：" + QString::number(array_player[current_player].get_score());
    int current_score = array_player[current_player].get_score();
    if(current_score > 21)
    {
        display += "（出局）";
    }
    switch (current_player) {
    case 0:
        ui->label_48->setText(display);
        if(current_score >= 21) ui->label_48->setStyleSheet("color: rgb(238, 29, 0);");
        break;
    case 1:
        ui->label_52->setText(display);
        if(current_score >= 21) ui->label_52->setStyleSheet("color: rgb(238, 29, 0);");
        break;
    case 2:
        ui->label_54->setText(display);
        if(current_score >= 21) ui->label_54->setStyleSheet("color: rgb(238, 29, 0);");
        break;
    case 3:
        ui->label_50->setText(display);
        if(current_score >= 21) ui->label_50->setStyleSheet("color: rgb(238, 29, 0);");
    }
    if(array_player[current_player].get_score() >= 21)
    {
        ui->pushButton_2->click();
    }
}


void _21_points::on_pushButton_2_clicked()//不抽了
{
    int k = current_player;
    for(int i = 0; i < playerNumber; i++)
    {
        k++;
        k %= playerNumber;
        if(array_player[k].get_score() <= 21)
            break;
    }
    if(current_player == k)
    {//结算
        ui->pushButton_3->click();
    }
    setCurrentPlayer(k);
}


void _21_points::on_pushButton_3_clicked()
{
    _21point_Board *board = new _21point_Board();
    QString text;
    for(int i = 0; i < playerNumber; i++)
    {
        text = array_player[i].get_name() + "点数：" + QString::number(array_player[i].get_score());
        if(array_player[i].get_score() > 21) text += "（出局）";
       board->labels[i]->setText(text);
    }
    int max_id=0;
    int flag=0;
    int max_score = -1;
    for(int i=0;i<playerNumber;i++)
    {
        if(array_player[i].get_score()>= max_score && array_player[i].get_score()<=21)
        {
            flag=1;
            max_id=i;
            max_score = array_player[i].get_score();
        }
    }
    if(flag)
    {
        board->labels[4]->setText(array_player[max_id].get_name() + "获胜！");
    }
    board->show();
    this->close();
    this->~_21_points();
}

