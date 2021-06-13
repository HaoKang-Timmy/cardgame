#include"include/player.h"
#include"include/card.h"
/**
 * @brief create a player
 * 
 */
player::player():score(0),playerHeap(),win(0),round(0){};


/**
 * @brief return this player's score
 * 
 * @return score
 */
int player::get_score()
{
    return this->score;
}

/**
 * @brief get a card for a player
 * 
 * @param card_fetched
 */
void player::player_fetchCard(card card_fetched)
{
    this->playerHeap.insertCard(card_fetched);
    score+=card_fetched.getPoint();
    return;
}
/**
 * @brief set win to 0 or 1
 * 
 * @param a 
 */
void player::set_win(bool a)
{
    this->win=a;
    return;
}
/**
 * @brief set round to 0 or 1
 * 
 * @param a 
 */
void player::set_round(bool a)
{
    this->round=a;
    return;
}

/**
 * @brief set score to a value
 * 
 * @param a 
 */
void player::set_score(int a)
{
    this->score=a;
    return;
}

QString player::get_name() const
{
    return name;
}

int player::get_num_cards() const
{
    return playerHeap.getSize();
}

/**
 * @brief init a player, used when every round is over
 * 
 */
void player::init_player()
{
    this->set_score(0);
    this->playerHeap.removeAllCards();
    this->set_win(0);
    this->set_round(0);
    return;
}

/**
 * @brief set the name for the player
 *
 */
void player::set_name(QString player_name)
{
    name = player_name;
}
