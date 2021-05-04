#include<iostream>
#include<ctime>
#include<algorithm>
#include "card.h"
using namespace std;

COLOR card::getColor() const
{
    return color;
}

int card::getPoint() const
{
    return point;
}

RANK card::getRank() const
{
    return rank;
}

bool cardHeap::isEmpty()
{
    return cards.empty();
}

//a normal card along with a extra value to determine its position in the random-order heap
class cardWithOrder : public card
{
private:
    int orderNum;//a random number assigned to the card
public:
    cardWithOrder(int newPoint, COLOR newColor, RANK newRank)
    : orderNum(rand()), card(newPoint, newColor, newRank) {}

    //an order rule for the card with the order number
    bool operator<(const cardWithOrder& c2){return orderNum<c2.orderNum;}
};

//initialize a new heap (already constructed) with random order cards
void cardHeap::initRandom()
{
    srand(time(0));
    vector<cardWithOrder> newCards;//a temporary vector used to contain and sort the cards at first
    for(int i = 0; i < 54; i++)
    {//respectively construct 54 cards
        int newPoint;
        COLOR newColor;
        RANK newRank;

        //set the values
        if(i < 52)//not a joker
        {
            newPoint = i % 13 + 1;
            newColor = (COLOR)(i / 13);
            newRank = (RANK)(i % 13);
        }
        else//is a joker
        {
            if(i == 52)
            {
                newColor = BIG_JOKER;
                newRank = JOKER;
                newPoint = 5;//这个point值是我先随便定的，后面再根据游戏机制调整
            }
            else if(i == 53)
            {
                newPoint = 5;//同上
                newColor = SMALL_JOKER;
                newRank = JOKER;
            }
        }
        cardWithOrder thisCard(newPoint, newColor, newRank);
        newCards.push_back(thisCard);//put the new card in the temporary vector
    }
    sort(newCards.begin(), newCards.end());//sort according to the ramdom interger assigned
                                           //to obtain a random-ordered card heap
    for(int i = 0; i < 54; i++) cards.push_back(newCards[i]);//insert the random-ordered cards to the heap one by one
}

//get a card from the top of the heap
card& cardHeap::fetchCard()
{
    card *ret = new card(cards.back());
    cards.pop_back();
    return *ret;
}

//put a card at the end of the card heap
void cardHeap::insertCard(card& cardToInsert)
{
    cards.push_back(cardToInsert);
}

//get the card at the ith position
card& cardHeap::peekCard(int index)
{
    if(index >= cards.size()) cout<<"no such card"<<endl;//这句错误提示可以结合我们的其他代码实现修改
                                                         //但按理来说可以避免遇到这种错误的情况
    return cards[index];
}

void cardHeap::removeAllCards()
{
    cards.clear();
    cards.shrink_to_fit();
}
