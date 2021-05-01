#include<iostream>
#include"card.h"
// used to make a class for player
class player
{
private:
    int score;// stores scores for players
    cardHeap playerHeap;//store cards for players
    bool win;// a flag to show whether a palyer wins or not
    bool round;// if it is 1, it is this player has go through this turn
public:
    player();
    ~player();
    int get_score();//used to show this player's score in a turn
    card& player_fetchCard();//get card from card Heap in a game
    void winning();// a flag to show whether he is winning or not
    void turn_to_round();// change flag round
    void init_player();//used to set to next round

};