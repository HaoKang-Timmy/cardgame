#ifndef _21_POINTS_H
#define _21_POINTS_H

#include <QMainWindow>
#include <QVector>
#include "include/card.h"
#include "include/player.h"
#include "mainwindow.h"
#include <QLabel>
#include <QUdpSocket>
#include <const.h>

extern MainWindow *w1;

namespace Ui {
class _21_points;
}

class _21_points : public QMainWindow
{
    Q_OBJECT

public:
    explicit _21_points(int numPlayers, bool isclient, int Seatid, QWidget *parent = nullptr);
    void setPlayers(const QString& p1, const QString& p2, const QString& p3 = "", const QString& p4 = "");
    void play();
    void init_interface();
    void setCurrentPlayer(int k);
    int getCurrentPlayer();
    void FetchcardClient(card fetchcard);
    card FetchcardServer();
    void EndfetchClient();
    void EndGame();
    void end_Overall_round();
    void new_Overall_round();
    ~_21_points();

protected:
    void sendMessage(GameMessage type);

private:
    Ui::_21_points *ui;
    int current_round;//当前轮数
    int playerNumber;//玩家实际人数
    player array_player[4];//玩家列表
    cardHeap playing_heap;
    int current_player;//当前轮到的玩家，0~3
    QLabel *player_card[4][11];
    QUdpSocket* client;
    qint16 port;
    bool isclient;
    int Seatid;

private slots:
    void processPendingDatagrams();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // _21_POINTS_H
