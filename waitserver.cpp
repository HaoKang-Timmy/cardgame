#include "waitserver.h"
#include "mainwindow.h"
#include "qtimer.h"
#include "qhostinfo.h"

waitserver::waitserver(int playernum, SeatStatus* player, QWidget *parent) :
    QWidget(parent), playernum(playernum)
{
    robotnum = 0;
    for(int i = 1; i <= 4; i++) {
        connected[i] = player[i];
        if(connected[i] == Robot) {
            robotnum++;
            this->player[i] = "robot";
        }
    }
    connect_num = 0;
    server = new QUdpSocket(this);
    port = 2333;
    server->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
           //readyRead()信号是每当有新的数据来临时就被触发
    connect(server, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    // 每 500ms 广播一次房间状态
    m_timer = new QTimer(this);
    this->connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTiming()));
    m_timer->start(500);
}

waitserver::~waitserver()
{
}


void waitserver::slotTiming()
{
    QByteArray wait_status;    //字节数组
    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&wait_status, QIODevice::WriteOnly);
    MessageType type = RoomStatus;
    out<<type<<connect_num;
    for(int i = 1; i <= 4; i++)
        out<<connected[i]<<player[i];
    server->writeDatagram(wait_status,wait_status.length(),QHostAddress::Broadcast, port);//将data中的数据发送
}


// 接收UDP信息
void waitserver::processPendingDatagrams()
{
    //hasPendingDatagrams返回true时表示至少有一个数据报在等待被读取
    while(server->hasPendingDatagrams())
    {
        QByteArray datagram;
        //pendingDatagramSize为返回第一个在等待读取报文的size，resize函数是把datagram的size归一化到参数size的大小一样
        datagram.resize(server->pendingDatagramSize());
        //将读取到的不大于datagram.size()大小数据输入到datagram.data()中，datagram.data()返回的是一个字节数组中存储
        //数据位置的指针
        server->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);//因为其属性为只读，所以是输入
        int messageType;    //此处的int为qint32，在Qt中，qint8为char，qint16为uint
        in >> messageType;    //读取1个32位长度的整型数据到messageTyep中
        QString Username;
        QString localHostName;
        QString Message;
        int Seatid;
        QByteArray wait_status;    //字节数组
        //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
        QDataStream out(&wait_status, QIODevice::WriteOnly);
        MessageType type;
        ErrCode Code;
        switch(messageType)
        {
            case NewParticipant:
                in >> localHostName >> Username>>Seatid;
                if(connected[Seatid] != Free) {
                    type = ErrMessage;
                    Message = "座位已有人";
                    Code = SeatFull;
                    out<<type<<localHostName<<Message<<Code;
                    server->writeDatagram(wait_status,wait_status.length(),QHostAddress::Broadcast, port);//将data中的数据发送
                }
                else {
                    connect_num++;
                    connected[Seatid] = Seated;
                    player[Seatid] = Username;
                }
                break;

            case ParticipantLeft:
                in>>Seatid;
                qDebug()<<Seatid;
                connected[Seatid] = Free;
                connect_num--;
                break;

            // 收到开始游戏请求，向所有玩家发送开始游戏指令
            case StartgameServer:
                in>>localHostName;
                qDebug()<<connect_num<<" "<<robotnum<<" "<<playernum;
                // 人数满足要求
                if(connect_num + robotnum == playernum) {
                    type = StartgameClient;
                    out<<type<<playernum;
                    for(int i = 1; i <= 4; i++)
                        out<<connected[i]<<player[i];
                } else {
                    type = ErrMessage;
                    Message = "人数不够";
                    Code = PlayerNotFull;
                    out<<type<<localHostName<<Message<<Code;
                }
                server->writeDatagram(wait_status,wait_status.length(),QHostAddress::Broadcast, port);//将data中的数据发送
                break;
        }
    }
}

