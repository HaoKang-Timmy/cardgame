#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
// used to make a class for player
class player
{
private:
    QString name;// the name of the player
    int score;// stores scores for players
    cardHeap playerHeap;//store cards for players
    bool win;// a flag to show whether a palyer wins or not
    bool round;// if it is 1, it is this player has go through this turn
    int num_win_round;//number of wins
public:
    player();
    ~player(){};
    int get_score();//used to show this player's score in a turn
    void player_fetchCard(card card_fetched);//get card from card Heap in a game
    QString get_name() const;
    void set_name(QString player_name);
    void set_win(bool a);// a flag to show whether he is winning or not
    void set_round(bool a);// change flag round
    void set_score(int a);
    void init_player();//used to set to next round
    int get_num_cards() const;
    void add_new_win();
    void clear_fetched_cards();
    int get_num_wins() const;
};
#endif
