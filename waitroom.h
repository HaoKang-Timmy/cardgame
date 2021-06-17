#ifndef WAITROOM_H
#define WAITROOM_H

#include <QWidget>
#include <QDebug>
#include <QUdpSocket>
#include "const.h"
#include "gameserver.h"
#include "waitserver.h"

namespace Ui {
class waitroom;
}

class selectNumPlayer;

class waitroom : public QWidget
{
    Q_OBJECT

public:
    explicit waitroom(TYPEGAMES typeGame, bool isServer, selectNumPlayer* s, waitserver* ws = nullptr, QWidget *parent = nullptr);
    ~waitroom();

protected:
    void sendMessage(MessageType type);

private:
    int Seatid;
    Ui::waitroom *ui;
    QUdpSocket* client;
    qint16 port;
    bool isServer;
    waitserver* ws;
    TYPEGAMES typeGame;
    gameserver* gs;
    selectNumPlayer* s;
    void Startgame(int playernum, QString player[]);

private slots:
    void getData(QString);//得到数据的槽函数
    void processPendingDatagrams();
    void on_StartgameBtn_clicked();
    void on_QuitRoomBtn_clicked();
};

#endif // WAITROOM_H
