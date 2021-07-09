#include "uno_game.h"
#include "ui_uno_game.h"
#include "include/card.h"

uno_game::uno_game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uno_game)
{
    ui->setupUi(this);
}


uno_game::~uno_game()
{
    delete ui;
}
