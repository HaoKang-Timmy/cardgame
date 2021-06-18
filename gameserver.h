#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QWidget>
#include <QUdpSocket>
#include <_21_points.h>
#include "const.h"

class gameserver : public QWidget
{
    Q_OBJECT
public:
    gameserver(TYPEGAMES typeGame, int playernum, int robotnum);

private:
    void sendMessage(GameMessage type);

private:
    QUdpSocket *server;
    qint16 port;
    _21_points *game;
    TYPEGAMES typeGame;
    int continue_num;
    int playernum;
    int robotnum;

private slots:
    void processPendingDatagrams();

};

#endif // GAMESERVER_H
