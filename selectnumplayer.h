#ifndef SELECTNUMPLAYER_H
#define SELECTNUMPLAYER_H

#include <QMainWindow>
enum TYPEGAMES {_21_POINTS};

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

private:
    Ui::selectNumPlayer *ui;
    TYPEGAMES typeGame;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SELECTNUMPLAYER_H
