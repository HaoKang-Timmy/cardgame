#include "waitroom.h"
#include "ui_waitroom.h"
#include "qhostinfo.h"
#include "_21_points.h"
#include <QMessageBox>
#include "mainwindow.h"

extern MainWindow *w1;
waitroom::waitroom(TYPEGAMES typeGame, bool isServer, selectNumPlayer* s, waitserver *ws, QWidget *parent) :
    QWidget(parent), typeGame(typeGame), isServer(isServer), ws(ws), s(s),
    ui(new Ui::waitroom)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,  true);
    client = new QUdpSocket(this);
    port = 2333;
    client->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
           //readyRead()信号是每当有新的数据来临时就被触发
    connect(client, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

waitroom::~waitroom()
{
    if(isServer)
        ws->~waitserver();
    delete client;
    delete ui;
}

void waitroom::getData(QString Seatid)
{
    this->Seatid = Seatid.toInt();
}

void waitroom::on_QuitRoomBtn_clicked()
{
    sendMessage(ParticipantLeft);
    this->close();
    this->~waitroom();
    w1->setHidden(false);
}

void waitroom::on_StartgameBtn_clicked()
{
    sendMessage(StartgameServer);
}

void waitroom::Startgame(int playernum, int robotnum, QString player[])
{
    switch (playernum) {
        case 2:
            if(typeGame == _21_POINTS)
            {
                _21_points *twentyone = new _21_points(2, 1, Seatid);
                twentyone->setPlayers(player[1], player[2]);
                this->close();
                twentyone->show();
            }
            break;
        case 3:
            if(typeGame == _21_POINTS)
            {
                _21_points *twentyone = new _21_points(3, 1, Seatid);
                twentyone->setPlayers(player[1], player[2], player[3]);
                this->close();
                twentyone->show();
            }
            break;
        case 4:
            if(typeGame == _21_POINTS)
            {
                _21_points *twentyone = new _21_points(4, 1, Seatid);
                twentyone->setPlayers(player[1], player[2], player[3], player[4]);
                this->close();
                twentyone->show();
            }
            break;
        }
    if(isServer) {
        gs = new gameserver(typeGame, playernum, robotnum);
    }

    this->~waitroom();
}

void waitroom::processPendingDatagrams()
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
        int messageType;    //此处的int为qint32，在Qt中，qint8为char，qint16为uint
        in >> messageType;    //读取1个32位长度的整型数据到messageTyep中
        QString Username,localHostName,ipAddress,message;
    //    QString time = QDateTime::currentDateTime()
      //          .toString("yyyy-MM-dd hh:mm:ss");//将当前的时间转化到括号中的形式
        int connect_num;
        SeatStatus connected[5];
        QString player[5];
        QLabel* label[5];
        label[1] = ui->player1;
        label[2] = ui->player2;
        label[3] = ui->player3;
        label[4] = ui->player4;
        localHostName = QHostInfo::localHostName();
        QString remoteHostName;
        switch(messageType)
        {
            case RoomStatus:
                in>>connect_num;
                ui->ConnectNum->setText(QString::number(connect_num));
                for(int i = 1; i <= 4; i++) {
                    in>>connected[i]>>player[i];
                    if(connected[i] == Seated)
                        label[i]->setText(player[i]);
                    else if(connected[i] == Robot) {
                        label[i]->setText("Robot");
                    }
                    else
                        label[i]->setText("等待玩家加入");
                }
                break;
            case StartgameClient:
                int playernum, robotnum;
                robotnum = 0;
                in>>playernum;
                for(int i = 1; i <= 4; i++) {
                    in>>connected[i]>>player[i];
                    if(connected[i] == Robot) {
                        robotnum++;
                    }
                }
                Startgame(playernum, robotnum, player);
                break;
            case ErrMessage:
                ErrCode code;
                in>>remoteHostName>>message>>code;
                if(localHostName == remoteHostName)
                    if(code == SeatFull) {
                        QMessageBox::information(this,tr("Error"),QStringLiteral("座位已被占用"),QMessageBox::Ok);
                        w1->setHidden(false);
                        this->close();
                    } else {
                        QMessageBox::information(this,tr("Error"),QStringLiteral("人数不够"),QMessageBox::Ok);
                    }
                break;
        }
    }
}

// 使用UDP广播发送信息，MessageType是指头文件中的枚举数据类型
//sendMessage即把本机的主机名，用户名+（消息内容后ip地址）广播出去
void waitroom::sendMessage(MessageType type)
{
    QByteArray data;    //字节数组
    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&data, QIODevice::WriteOnly);
    //将type，getUserName()，localHostName按照先后顺序送到out数据流中，消息类型type在最前面
    QString localHostName = QHostInfo::localHostName();
    out << type;

    switch(type)
    {
        case ParticipantLeft :
            out<<Seatid;
            break;
        case StartgameServer :
            out<<localHostName;
    }
    //一个udpSocket已经于一个端口bind在一起了，这里的data是out流中的data，最多可以传送8192个字节，但是建议不要超过
    //512个字节，因为这样虽然可以传送成功，但是这些数据需要在ip层分组，QHostAddress::Broadcast是指发送数据的目的地址
    //这里为本机所在地址的广播组内所有机器，即局域网广播发送
    client->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);//将data中的数据发送
}
