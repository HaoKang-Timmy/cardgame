#ifndef CARD_H
#define CARD_H
#include<QVector>
#include<QPixmap>

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
    card(int newPoint, COLOR newColor, RANK newRank, QString newPicPath): point(newPoint), color(newColor), rank(newRank), picPath(newPicPath) {};
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

class card_uno
{
public:

    card_uno(){}
    enum COLOR { BLUE, GREEN, RED, YELLOW, BLACK };
    enum CARD_TYPE { NUMBERIC, WILD, WILD_DRAW_FOUR, SKIP, REVERSE, DRAW_TWO };
    const QString BLUE_CARD_PATH = ":/uno_cards/blue/graph/uno_cards/blue/";
    const QString RED_CARD_PATH = ":/uno_cards/red/graph/uno_cards/red/";
    const QString GREEN_CARD_PATH = ":/uno_cards/green/graph/uno_cards/green/";
    const QString YELLOW_CARD_PATH = ":/uno_cards/yellow/graph/uno_cards/yellow/";
    const QString WILD_CARD_PATH = ":/uno_cards/wild/graph/uno_cards/wild/";

    // generate cards
    static void CreateAllCards();
    static void deleteAllCards();


    // get attrs
    COLOR getColor() const;
    CARD_TYPE getCardType() const;
    int getCardId() const;
    int getCardNum() const;
    const QPixmap& getPicture() const;

    static COLOR getColorById(int id);
    static CARD_TYPE getCardTypeById(int id);
    static int getCardNumById(int id);

    // get cards
    static void getAllCards(QVector<card_uno*>& cards);
    static card_uno* getCardById(int);

    // compares
    bool operator==(const card_uno& rhs) const;
    bool operator!=(const card_uno& rhs) const;

    int getProcesser() const;
    void setProcesser(int value);

    //dynamically change the color of the wild card
    void setColorForWild(COLOR new_color){if(cardType == WILD) color = new_color;}

    // check whether a card can be after this card
    bool next_card_give_OK(card_uno *next_card);
    bool this_card_give_OK(card_uno *last_card);

    // set the picture of the card
    void set_picture(QString path);

protected:
    COLOR color;
    CARD_TYPE cardType;
    int cardId;
    int cardNum;
    QPixmap cardPic;

private:
    static QVector<card_uno*> allCards;

    card_uno(COLOR color, CARD_TYPE cardType, int cardNum = -1);

    static int count;
    int processer;      // represents the card owner
    friend class card_uno_heap;
};

class card_uno_heap
{
private:
    QVector<card_uno*> cards;
//    bool is_public;
public:
    card_uno_heap(){}
    ~card_uno_heap(){}
    void init_random();
//    void init_player_7cards();
    card_uno *random_fetch_card();
    void insert_card(card_uno* card);
    int get_size() const{return cards.size();}
    bool is_empty() const {return cards.isEmpty();}
    bool no_cards_to_give(card_uno *last_card) const;
    card_uno *fetch_certain_card(card_uno *card);
    card_uno *operator[](int index){if(index < cards.size()) return cards[index]; else return nullptr;}
};

#endif
