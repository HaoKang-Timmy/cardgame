#include "gameserver.h"

gameserver::gameserver(TYPEGAMES typeGame, int playernum) : typeGame(typeGame)
{
    server = new QUdpSocket(this);
    port = 2333;
    server->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
           //readyRead()信号是每当有新的数据来临时就被触发
    connect(server, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    game = new _21_points(playernum, 0, 0);
    sendMessage(GameInit);
}

void gameserver::sendMessage(GameMessage type)
{
    QByteArray data;    //字节数组
    //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
    QDataStream out(&data, QIODevice::WriteOnly);
    //将type，getUserName()，localHostName按照先后顺序送到out数据流中，消息类型type在最前面
    out << type;

    switch(type)
    {
        case GameInit:
            break;
    }
    //一个udpSocket已经于一个端口bind在一起了，这里的data是out流中的data，最多可以传送8192个字节，但是建议不要超过
    //512个字节，因为这样虽然可以传送成功，但是这些数据需要在ip层分组，QHostAddress::Broadcast是指发送数据的目的地址
    //这里为本机所在地址的广播组内所有机器，即局域网广播发送
    server->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);//将data中的数据发送
}

void gameserver::processPendingDatagrams()
{
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
        card got;
        QByteArray data;    //字节数组
        //QDataStream类是将序列化的二进制数据送到io设备，因为其属性为只写
        QDataStream out(&data, QIODevice::WriteOnly);
        GameMessage type;
        switch(messageType)
        {
            case GameInit:
                break;
            case FetchCardServer:
                got = game->FetchcardServer();
                type = FetchCardClient;
                out<<type<<game->getCurrentPlayer()<<got.getPoint()<<got.getColor()<<got.getRank()<<got.getPicPath();
                server->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);
                break;
            case EndRoundServer:
                type = EndRoundClient;
                out<<type;
                server->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);
                break;
            case EndGameServer:
                type = EndGameClient;
                out<<type;
                server->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);
                this->~gameserver();
                break;
        }
    }
}
