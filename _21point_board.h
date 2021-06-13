#ifndef _21POINT_BOARD_H
#define _21POINT_BOARD_H

#include <QDialog>
#include "mainwindow.h"
#include <QLabel>
extern MainWindow *w1;
namespace Ui {
class _21point_Board;
}

class _21point_Board : public QDialog
{
    Q_OBJECT

public:
    explicit _21point_Board(QWidget *parent = nullptr);
    ~_21point_Board();
    QLabel *labels[5];

private slots:
    void on_pushButton_clicked();

private:
    Ui::_21point_Board *ui;
};

#endif // _21POINT_BOARD_H
