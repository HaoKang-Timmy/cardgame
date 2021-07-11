//#include<iostream>
#include<ctime>
#include<algorithm>
#include<QVector>
#include<QHash>
#include "include/card.h"
#include <QDebug>
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




int card_uno::count = 0;

QVector<card_uno*> card_uno::allCards = {};

void card_uno::CreateAllCards() {
    count = 0;
    QVector<card_uno*> card_unoss = {
        /*  0 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 0),
        /*  1 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 1),
        /*  2 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 1),
        /*  3 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 2),
        /*  4 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 2),
        /*  5 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 3),
        /*  6 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 3),
        /*  7 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 4),
        /*  8 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 4),
        /*  9 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 10 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 11 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 12 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 13 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 14 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 15 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 16 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 17 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 18 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 19 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::SKIP),
        /* 20 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::SKIP),
        /* 21 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::DRAW_TWO),
        /* 22 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::DRAW_TWO),
        /* 23 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::REVERSE),
        /* 24 */		new card_uno(card_uno::COLOR::RED, card_uno::CARD_TYPE::REVERSE),

        /* 25 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 0),
        /* 26 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 1),
        /* 27 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 1),
        /* 28 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 2),
        /* 29 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 2),
        /* 30 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 3),
        /* 31 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 3),
        /* 32 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 4),
        /* 33 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 4),
        /* 34 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 35 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 36 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 37 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 38 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 39 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 40 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 41 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 42 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 43 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 44 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::SKIP),
        /* 45 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::SKIP),
        /* 46 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::DRAW_TWO),
        /* 47 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::DRAW_TWO),
        /* 48 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::REVERSE),
        /* 49 */		new card_uno(card_uno::COLOR::YELLOW, card_uno::CARD_TYPE::REVERSE),

        /* 50 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 0),
        /* 51 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 1),
        /* 52 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 1),
        /* 53 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 2),
        /* 54 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 2),
        /* 55 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 3),
        /* 56 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 3),
        /* 57 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 4),
        /* 58 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 4),
        /* 59 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 60 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 61 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 62 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 63 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 64 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 65 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 66 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 67 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 68 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 69 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::SKIP),
        /* 70 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::SKIP),
        /* 71 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::DRAW_TWO),
        /* 72 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::DRAW_TWO),
        /* 73 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::REVERSE),
        /* 74 */		new card_uno(card_uno::COLOR::BLUE, card_uno::CARD_TYPE::REVERSE),

        /* 75 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 0),
        /* 76 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 1),
        /* 77 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 1),
        /* 78 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 2),
        /* 79 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 2),
        /* 80 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 3),
        /* 81 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 3),
        /* 82 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 4),
        /* 83 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 4),
        /* 84 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 85 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 5),
        /* 86 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 87 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 6),
        /* 88 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 89 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 7),
        /* 90 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 91 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 8),
        /* 92 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 93 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::NUMBERIC, 9),
        /* 94 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::SKIP),
        /* 95 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::SKIP),
        /* 96 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::DRAW_TWO),
        /* 97 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::DRAW_TWO),
        /* 98 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::REVERSE),
        /* 99 */		new card_uno(card_uno::COLOR::GREEN, card_uno::CARD_TYPE::REVERSE),

        /* 100 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD),
        /* 101 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD),
        /* 102 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD),
        /* 103 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD),

        /* 104 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD_DRAW_FOUR),
        /* 105 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD_DRAW_FOUR),
        /* 106 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD_DRAW_FOUR),
        /* 107 */		new card_uno(card_uno::COLOR::BLACK, card_uno::CARD_TYPE::WILD_DRAW_FOUR),

    };
    card_uno::allCards = card_unoss;
}

void card_uno::deleteAllCards()
{
    for (int i = 0; i < 108; ++i) {
        delete card_uno::allCards[i];
    }
}

card_uno::COLOR card_uno::getColor() const {
    return color;
}

card_uno::CARD_TYPE card_uno::getCardType() const {
    return cardType;
}

int card_uno::getCardId() const {
    return cardId;
}

int card_uno::getCardNum() const {
    return cardNum;
}

card_uno::COLOR card_uno::getColorById(int id)
{
    return COLOR(id/25);
}

card_uno::CARD_TYPE card_uno::getCardTypeById(int id)
{
    if (id >= 104 ) {
        return WILD_DRAW_FOUR;
    }
    else if (id >= 100) {
        return WILD;
    }
    else if (id % 25 < 19) {
        return NUMBERIC;
    }else if(id % 25 < 21){
        return SKIP;
    }else if(id % 25 < 21){
        return SKIP;
    }
    else if (id % 25 < 23) {
        return DRAW_TWO;
    }
    else if (id % 25 < 25) {
        return REVERSE;
    }
    assert(true);
    return WILD_DRAW_FOUR;
}

int card_uno::getCardNumById(int id)
{
    if (getCardTypeById(id) == NUMBERIC) {
        return (id % 25 - 1) / 2 + 1;
    }
    else {
        return -1;
    }
    return 0;
}

void card_uno::getAllCards(QVector<card_uno*>& card_unos)
{
    for (int i = 0; i < 108;++i) {
        card_unos.push_back(card_uno::allCards[i]);
    }
}

card_uno* card_uno::getCardById(int card_unoId) {
    return card_uno::allCards[card_unoId];
}

bool card_uno::operator==(const card_uno& rhs) const {
    return color == rhs.color &&
        cardType == rhs.cardType &&
        cardNum == rhs.cardNum;
}

bool card_uno::operator!=(const card_uno& rhs) const {
    return !(rhs == *this);
}

int card_uno::getProcesser() const
{
    return processer;
}

void card_uno::setProcesser(int value)
{
    processer = value;
}

card_uno::card_uno(COLOR color, card_uno::CARD_TYPE card_unoType, int card_unoNum) : color(color), cardType(card_unoType), cardNum(card_unoNum), cardId(count++) {
    processer = -1;
    QPixmap map;
    qDebug()<<"card_number: "<<card_unoNum;
    switch (color) {
    case RED:
        if(card_unoType == CARD_TYPE::NUMBERIC)
            map.load(RED_CARD_PATH + QString::number(card_unoNum) + ".png");
        else if(card_unoType == CARD_TYPE::SKIP)
            map.load(RED_CARD_PATH + "12.png");
        else if(card_unoType == CARD_TYPE::DRAW_TWO)
            map.load(RED_CARD_PATH + "10.png");
        else if(card_unoType == CARD_TYPE::REVERSE)
            map.load(RED_CARD_PATH + "11.png");
        break;
    case BLUE:
        if(card_unoType == CARD_TYPE::NUMBERIC)
            map.load(BLUE_CARD_PATH + QString::number(card_unoNum) + ".png");
        else if(card_unoType == CARD_TYPE::SKIP)
            map.load(BLUE_CARD_PATH + "12.png");
        else if(card_unoType == CARD_TYPE::DRAW_TWO)
            map.load(BLUE_CARD_PATH + "10.png");
        else if(card_unoType == CARD_TYPE::REVERSE)
            map.load(BLUE_CARD_PATH + "11.png");
        break;
    case YELLOW:
        if(card_unoType == CARD_TYPE::NUMBERIC)
            map.load(YELLOW_CARD_PATH + QString::number(card_unoNum) + ".png");
        else if(card_unoType == CARD_TYPE::SKIP)
            map.load(YELLOW_CARD_PATH + "12.png");
        else if(card_unoType == CARD_TYPE::DRAW_TWO)
            map.load(YELLOW_CARD_PATH + "10.png");
        else if(card_unoType == CARD_TYPE::REVERSE)
            map.load(YELLOW_CARD_PATH + "11.png");
        break;
    case GREEN:
        if(card_unoType == CARD_TYPE::NUMBERIC)
            map.load(GREEN_CARD_PATH + QString::number(card_unoNum) + ".png");
        else if(card_unoType == CARD_TYPE::SKIP)
            map.load(GREEN_CARD_PATH + "12.png");
        else if(card_unoType == CARD_TYPE::DRAW_TWO)
            map.load(GREEN_CARD_PATH + "10.png");
        else if(card_unoType == CARD_TYPE::REVERSE)
            map.load(GREEN_CARD_PATH + "11.png");
        break;
    case BLACK:
        if(card_unoType == CARD_TYPE::WILD)
            map.load(":/uno_cards/wild/graph/uno_cards/wild/Wild.png");
        else if(card_unoType == CARD_TYPE::WILD_DRAW_FOUR)
            map.load(":/uno_cards/wild/graph/uno_cards/wild/DrawFour.png");
    default:
        break;
    }
    map = map.scaled(120, 200, Qt::KeepAspectRatio);
    cardPic = map;
}


bool compare(QPair<card_uno*, int>a, QPair<card_uno*, int>b)
{
    return a.second < b.second;
}
/**
 * @brief initialize the heap with all cards in a random order
 */
void card_uno_heap::init_random()
{
    card_uno::CreateAllCards();
    std::srand(time(NULL));
    QVector<QPair<card_uno*, int>> random;
    qDebug()<<"number of all cards: "<<card_uno::allCards.size();
    for(int i = 0; i < card_uno::allCards.size(); i++)
    {
        if(card_uno::allCards[i]->cardType != card_uno::WILD)
            random.append(QPair<card_uno*, int>(card_uno::allCards[i], std::rand()));
    }
    std::sort(random.begin(), random.end(), compare);
    for(int i = 0; i < random.size(); i++) cards.append(random[i].first);
}

/**
 * @brief get a uno card from a random place in the heap
 * @return the pointer to the card object
 */
card_uno *card_uno_heap::random_fetch_card()
{
    std::srand(time(NULL));
    int randnum = std::rand()%(cards.size());
    card_uno *ret = cards[randnum];
    cards.removeAt(randnum);
    return ret;
}

/**
 * @brief put a card into the heap
 * @param card the pointer to that card
 */
void card_uno_heap::insert_card(card_uno* card)
{
    cards.append(card);
}

/**
 * @brief check whether a card can be after this card
 * @param next_card the card to be given next
 * @return true if OK
 */
bool card_uno::next_card_give_OK(card_uno *next_card)
{
    if(next_card->color == BLACK) return true;
    //if(next_card->cardType == DRAW_TWO && this->cardType == WILD_DRAW_FOUR) return true;
    if(this->cardType == WILD_DRAW_FOUR || this->cardType == DRAW_TWO)
    {
        if(next_card->cardType == DRAW_TWO || next_card->cardType == WILD_DRAW_FOUR) return true;
        else return false;
    }
    if(this->cardType == next_card->cardType && this->cardType != NUMBERIC) return true;
    if(this->color == next_card->color) return true;
    if(this->cardType == NUMBERIC && next_card->cardType == NUMBERIC && this->cardNum == next_card->cardNum) return true;
    return false;
}

/**
 * @brief check whether this card can be given after a card
 * @param last_card the last given card
 * @return true if OK
 */
bool card_uno::this_card_give_OK(card_uno *last_card)
{
    if(last_card == nullptr) return true;
    return last_card->next_card_give_OK(this);
}

/**
 * @brief check whether there is no card in this heap can be given after a card
 * @param last_card
 * @return true if no
 */
bool card_uno_heap::no_cards_to_give(card_uno *last_card) const
{
    for(auto i = cards.begin(); i != cards.end(); i++)
    {
        if((*i)->this_card_give_OK(last_card)) return false;
    }
    return true;
}

/**
 * @brief fetch a specialized card from the heap
 * @param card the pointer to the card
 * @return the pointer to the card if the card is in the heap, else return NULL
 */
card_uno *card_uno_heap::fetch_certain_card(card_uno *card)
{
    int index = cards.indexOf(card);
    if(index == -1) return NULL;
    else cards.remove(index);
    return card;
}

/**
 * @brief card_uno::getPicture
 * @return the pixmap object of the card, containing the picture
 */
const QPixmap& card_uno::getPicture() const
{
    return this->cardPic;
}

void card_uno::set_picture(QString path)
{
    QPixmap map;
    map.load(path);
    map = map.scaled(120, 200, Qt::KeepAspectRatio);
    this->cardPic = map;
}
