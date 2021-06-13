#ifndef WAITROOM_H
#define WAITROOM_H

#include <QMainWindow>

namespace Ui {
class WaitRoom;
}

class WaitRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit WaitRoom(QWidget *parent = nullptr);
    ~WaitRoom();

private:
    Ui::WaitRoom *ui;
};

#endif // WAITROOM_H
