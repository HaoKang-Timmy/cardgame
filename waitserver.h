#ifndef WAITSERVER_H
#define WAITSERVER_H

#include <QWidget>
#include <QUdpSocket>
#include "const.h"


class waitserver : public QWidget
{
    Q_OBJECT

public:
    explicit waitserver(int playernum, SeatStatus *player, QWidget *parent = nullptr);
    ~waitserver();

private:
    // 该房间需要的玩家数量
    int playernum;
    // 该房间机器人数量
    int robotnum;
    SeatStatus connected[5];
    // 当前的玩家数量
    int connect_num;
    QString player[5];
    QUdpSocket *server;
    qint16 port;
    // 计时器， 定时发送房间状态
    QTimer *m_timer;

private slots:
    void processPendingDatagrams();
    void slotTiming();
};

#endif // WAITSERVER_H
