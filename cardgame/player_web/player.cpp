#include"include/player.h"
#include"include/card.h"

#include<stdlib.h>
#include<ctime>
#include<QDebug>

/**
 * @brief create a player
 * 
 */
player::player():score(0),playerHeap(),win(0),round(0), num_win_round(0){};


/**
 * @brief return this player's score
 * 
 * @return score
 */
int player::get_score() const
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

/**
 * @brief increment the number of wins of the player
 *
 */
void player::add_new_win()
{
    num_win_round++;
}

void player::clear_fetched_cards()
{
    playerHeap.removeAllCards();
}

int player::get_num_wins() const
{
    return num_win_round;
}
bool player::self_judge()
{
    double p,q,r;
    int seed=time(0);
    srand(seed);
    p=(double)(rand()%10000)/10000;
    r=get_score();
    q=(21-r)/13;
    if(q<0)
       return 0;
    return p<q;
}

/**
 * @brief set all flag to false
 */
void player_uno::set_false()
{
    has_draw_two[card_uno::RED] = false;
    has_draw_two[card_uno::BLUE] = false;
    has_draw_two[card_uno::GREEN] = false;
    has_draw_two[card_uno::YELLOW] = false;
    has_reverse[card_uno::RED] = false;
    has_reverse[card_uno::BLUE] = false;
    has_reverse[card_uno::GREEN] = false;
    has_reverse[card_uno::YELLOW] = false;
    has_skip[card_uno::RED] = false;
    has_skip[card_uno::BLUE] = false;
    has_skip[card_uno::GREEN] = false;
    has_skip[card_uno::YELLOW] = false;
    has_wild[card_uno::WILD] = false;
    has_wild[card_uno::WILD_DRAW_FOUR] = false;
}

player_uno::player_uno(bool human) : is_human(human)
{
    set_false();
}

/**
 * @brief check whether the player have no card satisfying the condition to be given out
 * @param last_card the card given out by the last player in the round
 * @return true if no
 */
bool player_uno::no_cards_to_give(card_uno *last_card) const
{
    return player_heap.no_cards_to_give(last_card);
}

/**
 * @brief the player giving out a specialized card which will be deleted from the player's heap
 * @param card the pointer to the given card
 * @return pointer to the given card, or NULL if that card is not in the player's heap
 */
card_uno *player_uno::give_card(card_uno *card)
{
    card_uno *ret = player_heap.fetch_certain_card(card);
    if(ret)
    {
        last_card_given = ret;
        return ret;
    }
    return NULL;
}

/**
 * @brief add a card into the heap of the player
 * @param card the pointer to the card
 */
void player_uno::fetch_card(card_uno *card)
{
    player_heap.insert_card(card);
}

/**
 * @brief update the flags in the object showing which card can be given and whether the special cards exist in the heap
 */
void player_uno::update_card_status(card_uno *last_card)
{
    set_false();
    for(int i = 0; i < player_heap.get_size(); i++)
    {
        const card_uno *thiscard = player_heap[i];
        switch(thiscard->getCardType())
        {
        case card_uno::DRAW_TWO:
            has_draw_two[thiscard->getColor()] = true;
            break;
        case card_uno::SKIP:
            has_skip[thiscard->getColor()] = true;
            break;
        case card_uno::REVERSE:
            has_reverse[thiscard->getColor()] = true;
            break;
        case card_uno::WILD:
            has_wild[card_uno::WILD] = true;
            break;
        case card_uno::WILD_DRAW_FOUR:
            has_wild[card_uno::WILD_DRAW_FOUR] = true;
            break;
        default:
            break;
        }
    }

    OK_flag.clear();
    for(int i = 0; i < player_heap.get_size(); i++)
    {
        if(player_heap[i]->this_card_give_OK(last_card)) OK_flag.append(true);
        else OK_flag.append(false);
    }
}
