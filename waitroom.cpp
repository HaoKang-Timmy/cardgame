#include "waitroom.h"
#include "ui_waitroom.h"

WaitRoom::WaitRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WaitRoom)
{
    ui->setupUi(this);
}

WaitRoom::~WaitRoom()
{
    delete ui;
}
