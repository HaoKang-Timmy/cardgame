#ifndef UNO_GAME_H
#define UNO_GAME_H
#include "include/card.h"
#include "include/player.h"
#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>

extern MainWindow *w1;

namespace Ui {
class uno_game;
}

class uno_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit uno_game(QWidget *parent = nullptr);
    ~uno_game();
    void game_init();//does any preparation before the game starts
    void player_fetch_card(int player_index, int numcard);//玩家抽牌
    void player_give_card(int player_index, card_uno *card);//玩家出牌
    void update_player_card_display();//update the cards displayed on the screen
    void update_last_card_display();//update the last card given out displayed on the screen
    void reverse();//change the direction
    void update_direction_display();
    void go_on_to_the_next_player();


private slots:

    void slotTiming();

    void on_end_clicked();

    void on_button_card0_clicked();

    void on_button_card1_clicked();

    void on_button_card2_clicked();

    void on_button_card3_clicked();

    void on_button_card4_clicked();

    void on_button_card5_clicked();

    void on_button_card6_clicked();

    void on_button_card7_clicked();

    void on_button_card8_clicked();

    void on_button_card9_clicked();

    void on_button_card10_clicked();

    void on_button_card11_clicked();

    void on_button_card12_clicked();

    void on_button_card13_clicked();

    void on_button_card14_clicked();

private:
    Ui::uno_game *ui;
    card_uno_heap public_cards;
    QLabel *player_card_list[15];// the array of the human player's card labels
    QPushButton *player_card_button_list[15];//the array of the buttons (transparent) for those cards
    QLabel *current_player_indicator[4];
    QMap <QLabel*, card_uno*> player_cards_mapping;//the mapping between card objects and the labels on the interface
    int current_player = 0;//0-the player, 1-robot1, 2-robot2, 3-robot3
    bool direction_is_clockwise = true;
    int draw_card_number_accumulate = 0;//累计的+2/+4数量
    player_uno *players[4];//the player objects, the 0th object is the real player
    card_uno *last_card = nullptr;
    void update_card_display(QLabel *card_display, card_uno *card, int rotate_90);
    bool skip_flag = false;
    QTimer *m_timer;
};

#endif // UNO_GAME_H
