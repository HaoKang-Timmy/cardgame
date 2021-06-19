#include "_21_points.h"
#include "ui__21_points.h"
#include "_21point_board.h"
#include "QDebug"
#include "mainwindow.h"
#include <QMessageBox>
extern MainWindow *w1;

_21_points::_21_points(int numPlayers, bool isclient, int Seatid, QWidget *parent) :
    QMainWindow(parent), playerNumber(numPlayers), isclient(isclient), Seatid(Seatid),
    ui(new Ui::_21_points)
{
    ui->setupUi(this);
    //以下这几行应该是加在gameinit里的，但是因为新的游戏逻辑还没有正式加入，所以先放这里
    current_round = 1;//第一局

    //隐藏一局结束时的按钮和提示
    ui->pushButton_3->setHidden(true);
    ui->pushButton_4->setHidden(true);

    client = new QUdpSocket(this);

    port = 2333;
    client->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
           //readyRead()信号是每当有新的数据来临时就被触发
    connect(client, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    qDebug()<<"game"<<Seatid;
    /*init_interface();
    current_player = 0;
    array_player[0].set_round(1);
    ui->label_56->setHidden(true);
    ui->label_57->setHidden(true);
    ui->label_58->setHidden(true);*/
    setWindowTitle("21点");
}

_21_points::~_21_points()
{
    delete client;
    delete ui;
}

void _21_points::closeEvent(QCloseEvent *event)
{
    w1->setHidden(false);
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
    switch (Seatid) {
    case 1:
        ui->label_47->setText(ui->label_47->text() + "（我）");
        break;
    case 2:
        ui->label_51->setText(ui->label_51->text() + "（我）");
        break;
    case 3:
        ui->label_53->setText(ui->label_53->text() + "（我）");
        break;
    case 4:
        ui->label_49->setText(ui->label_49->text() + "（我）");
    }

}

int _21_points::getCurrentPlayer()
{
    return current_player;
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
        if(playerNumber >= 3)
        ui->label_57->setHidden(false);
        break;
    case 3:
        if(playerNumber == 4)
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
        ui->label_62->setHidden(true);
    }
    if(playerNumber == 2)
    {
        ui->label_53->setHidden(true);
        ui->label_54->setHidden(true);
        ui->label_61->setHidden(true);
    }
    ui->label_64->setHidden(true);
}

void _21_points::on_pushButton_clicked()//抽牌
{
    /*qDebug()<<current_player;
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
    }*/
    sendMessage(FetchCardServer);
}

card _21_points::FetchcardServer()
{
    if(playing_heap.isEmpty())
        playing_heap.initRandom(false);
    card got = playing_heap.fetchCard();
    return got;
}

void _21_points::FetchcardClient(card got)//抽牌
{
    /*qDebug()<<current_player;
    if(playing_heap.isEmpty())
        playing_heap.initRandom(false);
    card got = playing_heap.fetchCard();*/
    array_player[current_player].player_fetchCard(got);
    if(current_player == 0 || current_player == 2)
    {
        player_card[current_player][array_player[current_player].get_num_cards()-1]->setStyleSheet("background-image: url(" + got.getPicPath() + ");");
    }
    else
    {
        QPixmap pix;
        //qDebug()<<got.getPicPath();
        pix.load(got.getPicPath());
        QTransform trans;
        trans.rotate(90);
        player_card[current_player][array_player[current_player].get_num_cards()-1]->setPixmap(pix.transformed(trans,Qt::SmoothTransformation));
    }
    QString display = "当前点数：" + QString::number(array_player[current_player].get_score());
    int current_score = array_player[current_player].get_score();
    if(current_score >= 21)
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
        qDebug()<<"score >";
        if(!isclient)
            ui->pushButton_2->click();
    }
}


void _21_points::on_pushButton_2_clicked()//不抽了
{
    /*int k = current_player;
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
    setCurrentPlayer(k);*/
    sendMessage(EndFetchServer);
}

void _21_points::EndfetchClient()
{
    int k = current_player + 1;
    //qDebug()<<"EndRound"<<k;
    if(k == playerNumber && !isclient)
        sendMessage(EndRoundServer);
    else
        setCurrentPlayer(k);
    if(k == Seatid - 1)
    {
        ui->pushButton->setHidden(false);
        ui->pushButton_2->setHidden(false);
    }
    else
    {
        ui->pushButton->setHidden(true);
        ui->pushButton_2->setHidden(true);
    }
    /*for(int i = 0; i < playerNumber; i++)
    {
        k++;
        if(k == playerNumber)
            sendMessage(EndGameServer);
        if(array_player[k].get_score() <= 21)
            break;
    }*/
    //setCurrentPlayer(k);
}

void _21_points::EndGame()
{
    _21point_Board *board = new _21point_Board(this);
    QString text;
    int i;
    for(i = 0; i < playerNumber; i++)
    {
        text = array_player[i].get_name() + "：获胜" + QString::number(array_player[i].get_num_wins()) + "局";
        board->labels[i]->setText(text);
    }
    for(; i < 4; i++)
    {
        qDebug()<<"i"<<i;
        board->labels[i]->setText("");//只显示已有的玩家的获胜次数，其余的清空
    }
    board->labels[4]->setHidden(true);//这种情况下不需要再显示哪个玩家获胜，这个label可以删掉
    qDebug()<<"4";
    this->setHidden(true);
    if(isclient)
        board->show();
    qDebug()<<"board show";
//    this->~_21_points();
}

void _21_points::sendMessage(GameMessage type)
{
    QByteArray data;    //字节数组
    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&data, QIODevice::WriteOnly);
    //将type，getUserName()，localHostName按照先后顺序送到out数据流中，消息类型type在最前面
    out << type;
    if(type == EndGameServer) {
        out<<Seatid;
    }
    //一个udpSocket已经于一个端口bind在一起了，这里的data是out流中的data，最多可以传送8192个字节，但是建议不要超过
    //512个字节，因为这样虽然可以传送成功，但是这些数据需要在ip层分组，QHostAddress::Broadcast是指发送数据的目的地址
    //这里为本机所在地址的广播组内所有机器，即局域网广播发送
    client->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);//将data中的数据发送
}

void _21_points::processPendingDatagrams()
{
    while(client->hasPendingDatagrams())
    {
        QByteArray datagram;
        //pendingDatagramSize为返回第一个在等待读取报文的size，resize函数是把datagram的size归一化到参数size的大小一样
        datagram.resize(client->pendingDatagramSize());
        //将读取到的不大于datagram.size()大小数据输入到datagram.data()中，datagram.data()返回的是一个字节数组中存储
        //数据位置的指针
        client->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);//因为其属性为只读，所以是输入
        int current_player;
        int point;//point get by the player if fetched
        COLOR color;//pattern of the card
        RANK rank;
        QString picPath;
        int messageType;    //此处的int为qint32，在Qt中，qint8为char，qint16为uint
        in >> messageType;    //读取1个32位长度的整型数据到messageTyep中
        switch(messageType)
        {
            case GameInit:
                init_interface();
                this->current_player = 0;
                array_player[0].set_round(1);
                ui->label_56->setHidden(true);
                ui->label_57->setHidden(true);
                ui->label_58->setHidden(true);
                if(Seatid != 1)
                {
                    ui->pushButton->setHidden(true);
                    ui->pushButton_2->setHidden(true);
                }
                break;
            case FetchCardClient:
                in>>current_player>>point>>color>>rank>>picPath;
                FetchcardClient(card(point, color, rank, picPath));
                break;
            case EndFetchClient:
                EndfetchClient();
                break;
            case EndRoundClient:
                end_Overall_round();
                break;
            case NewRoundClient:
                new_Overall_round();
                break;
            case EndGameClient:
                qDebug()<<"111";
                int seatid;
                in>>seatid;
                qDebug()<<"seatid:" + QString::number(seatid);
                QString message;
                if(isclient && Seatid != seatid) {
                    message = QString::number(seatid) + "号玩家退出，游戏结束";
                    QMessageBox::information(this,tr("Error"),message,QMessageBox::Ok);
                }
                qDebug()<<"222";
                EndGame();
                qDebug()<<"333";
        }
    }
}
void _21_points::end_Overall_round()//完整的一轮（每个玩家都轮过一次）结束
{
    //无论如何，结束时都隐藏抽牌的按钮
    ui->pushButton->setHidden(true);
    ui->pushButton_2->setHidden(true);
    //先判断是否有玩家获胜，设置提示
    bool win_flag = false;
    bool equal_flag = true;
    int max_score = -1;
    int max_id = 0;
    for(int i = 0; i < playerNumber; i++)
    {
        if(array_player[i].get_score() >= 21) equal_flag = false;
        if(array_player[i].get_score() > max_score && array_player[i].get_score() < 21)
        {
            win_flag = true;
            if(i != 0) equal_flag = false;
            max_id=i;
            max_score = array_player[i].get_score();
        }
        else if(array_player[i].get_score() < max_score) equal_flag = false;
    }
    if(equal_flag) ui->label_63->setText("第" + QString::number(current_round) + "局为平局");
    else if(win_flag)
    {
        array_player[max_id].add_new_win();
        ui->label_63->setText("第" + QString::number(current_round) + "局获胜玩家为" + array_player[max_id].get_name() + "!");
    }
    else ui->label_63->setText("第" + QString::number(current_round) + "局没有玩家获胜");
//这里要有一段判断是不是server,如果是server则显示是否继续的按钮
    if(true/* == isServer*/)
    {
        ui->pushButton_3->setHidden(false);
        ui->pushButton_4->setHidden(false);
        ui->label_64->setHidden(false);
    }
}

void _21_points::new_Overall_round()//开始新的一轮
{
    current_round ++;
    ui->label_63->setText("第" + QString::number(current_round) + "局");
    for(int i = 0; i < playerNumber; i++)
    {
        array_player[i].clear_fetched_cards();//玩家原来抽的牌清空，不过总牌堆不用重置，继续抽即可
        array_player[i].set_score(0);//点数清空
        for(int j = 0; j < 11; j++)
        {//重置玩家抽牌的显示
            player_card[i][j]->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
            if(i == 1 || i == 3)//之前忘了左右两边的牌是用pixmap画的了，大意了
            {
                QPixmap empty = QPixmap();
                player_card[i][j]->setPixmap(empty);
            }
        }
    }
    //更新局数显示
    ui->label_59->setText("已获胜局数：" + QString::number(array_player[0].get_num_wins()));
    ui->label_60->setText("已获胜局数：" + QString::number(array_player[1].get_num_wins()));
    ui->label_61->setText("已获胜局数：" + QString::number(array_player[2].get_num_wins()));
    ui->label_62->setText("已获胜局数：" + QString::number(array_player[3].get_num_wins()));

    ui->label_48->setText("当前点数：0");
    ui->label_48->setStyleSheet("color: rgb(255, 255, 255);");//字体颜色恢复成白色
    ui->label_52->setText("当前点数：0");
    ui->label_52->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_54->setText("当前点数：0");
    ui->label_54->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_50->setText("当前点数：0");
    ui->label_50->setStyleSheet("color: rgb(255, 255, 255);");

    //把一局结束之后选择是否继续的按钮和label藏起来，应该也要加到gameinit里
    ui->pushButton_3->setHidden(true);
    ui->pushButton_4->setHidden(true);
    ui->label_64->setHidden(true);

    //以下是gameinit里的部分逻辑
    this->current_player = 0;
    array_player[0].set_round(1);
    ui->label_56->setHidden(true);
    ui->label_57->setHidden(true);
    ui->label_58->setHidden(true);
    qDebug()<<isclient<<" "<<Seatid;
    if(Seatid == 1)
    {
        ui->pushButton->setHidden(false);
        ui->pushButton_2->setHidden(false);
    }
    setCurrentPlayer(0);
}


void _21_points::on_pushButton_3_clicked()//点击继续游戏按钮
{
    //new_Overall_round();//开始新一局
    sendMessage(NewRoundServer);
    ui->label_64->setText("等待其他玩家选择...");
}


void _21_points::on_pushButton_4_clicked()//点击结束游戏按钮
{
    /*_21point_Board *board = new _21point_Board();
    QString text;
    int i;
    for(i = 0; i < playerNumber; i++)
    {
        text = array_player[i].get_name() + "：获胜" + QString::number(array_player[i].get_num_wins()) + "局";
        board->labels[i]->setText(text);
    }
    for(; i < 4; i++)
        board->labels[i]->setText("");//只显示已有的玩家的获胜次数，其余的清空
    board->labels[4]->setHidden(true);//这种情况下不需要再显示哪个玩家获胜，这个label可以删掉
    this->setHidden(true);
    if(isclient)
        board->show();
    this->~_21_points();*/
    sendMessage(EndGameServer);
}

