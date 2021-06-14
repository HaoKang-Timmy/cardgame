//#include<iostream>
#include<ctime>
#include<algorithm>
#include<QVector>
#include "include/card.h"

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

void card::setPicPath()
{
    picPath = getCardPic(this->color, this->rank);
}

bool cardHeap::isEmpty()
{
    return cards.empty();
}

int cardHeap::getSize() const
{
    return cards.size();
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
void cardHeap::initRandom(bool withJokers)
{
    srand(time(0));
    QVector<cardWithOrder> newCards;//a temporary QVector used to contain and sort the cards at first
    int j;
    if(withJokers) j = 54;
    else j = 52;
    for(int i = 0; i < j; i++)
    {//respectively construct j cards
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
        thisCard.setPicPath();
        newCards.push_back(thisCard);//put the new card in the temporary QVector
    }
    std::sort(newCards.begin(), newCards.end());//sort according to the ramdom interger assigned
                                           //to obtain a random-ordered card heap
    for(int i = 0; i < j; i++) cards.push_back(newCards[i]);//insert the random-ordered cards to the heap one by one
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
    return cards[index];
}

void cardHeap::removeAllCards()
{
    cards.clear();
    cards.shrink_to_fit();
}

QString& card::getPicPath()
{
    return picPath;
}

QString getCardPic(COLOR color, RANK rank)
{
    QString ret = ":/cards/";
    switch (color) {
    case CLUBS:
        ret += "Club/graph/cards/Club/C_";
        break;
    case HEARTS:
        ret += "Heart/graph/cards/Heart/H_";
        break;
    case SPADES:
        ret += "spade/graph/cards/Spade/S_";
        break;
    case DIAMONDS:
        ret += "Diamond/graph/cards/Diamond/D_";
        break;
    default: //大小王的图片暂时还没有。
        break;
    }
    switch (rank) {
    case ACE:
        ret += "A";
        break;
    case TWO:
        ret += "2";
        break;
    case THREE:
        ret += "3";
        break;
    case FOUR:
        ret += "4";
        break;
    case FIVE:
        ret += "5";
        break;
    case SIX:
        ret += "6";
        break;
    case SEVEN:
        ret += "7";
        break;
    case EIGHT:
        ret += "8";
        break;
    case NINE:
        ret += "9";
        break;
    case TEN:
        ret += "10";
        break;
    case JACK:
        ret += "J";
        break;
    case QUEEN:
        ret += "Q";
        break;
    case KING:
        ret += "K";
        break;
    default:
        break;
    }
    ret += ".png";
    return ret;
}
