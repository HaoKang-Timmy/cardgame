#ifndef SELECTNUMPLAYER_H
#define SELECTNUMPLAYER_H

#include <QMainWindow>
#include "mainwindow.h"
enum TYPEGAMES {_21_POINTS};
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
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

private:
    Ui::selectNumPlayer *ui;
    TYPEGAMES typeGame;
};

#endif // SELECTNUMPLAYER_H
