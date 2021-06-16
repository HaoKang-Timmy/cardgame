#ifndef CARD_H
#define CARD_H
#include<QVector>

enum COLOR{SPADES, HEARTS, DIAMONDS, CLUBS, BIG_JOKER, SMALL_JOKER};
enum RANK{ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, JOKER};

class card
{
private:
    int point;//point get by the player if fetched
    COLOR color;//pattern of the card
    RANK rank;
    QString picPath;
public:
    card(){};
    card(int newPoint, COLOR newColor, RANK newRank): point(newPoint), color(newColor), rank(newRank) {};
    card(int newPoint, COLOR newColor, RANK newRank): point(newPoint), color(newColor), rank(newRank) {};
    card(int newPoint, COLOR newColor, RANK newRank): point(newPoint), color(newColor), rank(newRank) {};
    ~card(){};
    int getPoint() const;
    COLOR getColor() const;
    RANK getRank() const;
    void setPicPath();
    QString& getPicPath();
};


class cardHeap
{
private:
    QVector<card> cards;//the container of cards
public:
    cardHeap() {};
    ~cardHeap() {};
    bool isEmpty();
    int getSize() const;
    void initRandom(bool withJokers);
    card& fetchCard();
    void insertCard(card& cardToInsert);
    card& peekCard(int index);
    void removeAllCards();
};

QString getCardPic(COLOR color, RANK rank);
#endif
