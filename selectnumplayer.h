#ifndef SELECTNUMPLAYER_H
#define SELECTNUMPLAYER_H

#include <QMainWindow>
#include "mainwindow.h"
#include "waitroom.h"
#include "waitserver.h"
#include <QtNetwork>

extern MainWindow *w1;

namespace Ui {
class selectNumPlayer;
}

class selectNumPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit selectNumPlayer(QWidget *parent = nullptr, TYPEGAMES type = _21_POINTS);
    ~selectNumPlayer();

private slots:
    //void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_EnterBtn_clicked();

    void on_CreateBtn_clicked();

protected:
    void sendMessage(MessageType type);

signals:
  void sendData(QString);//发送数据的信号，不需要实体函数，在头文件定义就可以

private:
    Ui::selectNumPlayer *ui;
    TYPEGAMES typeGame;
    qint16 port;
    waitroom* wt;
    waitserver* ws;
    QUdpSocket *server;
    QUdpSocket *client;
};

#endif // SELECTNUMPLAYER_H
