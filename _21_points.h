#ifndef _21_POINTS_H
#define _21_POINTS_H

#include <QMainWindow>
#include <QVector>
#include "include/card.h"
#include "include/player.h"
#include "mainwindow.h"
#include <QLabel>
extern MainWindow *w1;

namespace Ui {
class _21_points;
}

class _21_points : public QMainWindow
{
    Q_OBJECT

public:
    explicit _21_points(QWidget *parent = nullptr, int numPlayers = 4);
    void setPlayers(const QString& p1, const QString& p2, const QString& p3 = "", const QString& p4 = "");
    void play();
    void init_interface();
    void setCurrentPlayer(int k);
    ~_21_points();

private:
    Ui::_21_points *ui;
    int playerNumber;//玩家实际人数
    player array_player[4];//玩家列表
    cardHeap playing_heap;
    int current_player;//当前轮到的玩家，0~3
    QLabel *player_card[4][11];

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // _21_POINTS_H
