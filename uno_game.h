#ifndef UNO_GAME_H
#define UNO_GAME_H
#include "include/card.h"
#include "include/player.h"
#include <QLabel>
#include <QMainWindow>

namespace Ui {
class uno_game;
}

class uno_game : public QMainWindow
{
    Q_OBJECT

public:
    explicit uno_game(QWidget *parent = nullptr);
    ~uno_game();
    void init_interface();
    void init_color();//
    void init_players();
    void player_fetch_card(int player_index, int numcard);//玩家抽牌
    void player_give_card(card_uno *card);//玩家出牌
    void update_player_card_display();
    void reverse();

    /*以上这几个函数暂时还没写*/

private:
    Ui::uno_game *ui;
    QMap <QLabel*, card_uno*> player_cards;//the mapping between card objects and the labels on the interface
    int current_player = 0;//0-the player, 1-robot1, 2-robot2, 3-robot3
    bool direction_is_clockwise = true;
    int draw_card_number_accumulate;//累计的+2/+4数量
};

#endif // UNO_GAME_H
