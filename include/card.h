#include <iostream>
#include <queue>
using namespace std;

enum COLOR{RED_PEACH, BLACK_PEACH, RED_RECT, BLACK_FLOWER, BIG_KING, SMALL_KING};
class card
{
private:
    int point;
    COLOR color;
public:
    card();
    card(int newPoint, COLOR newColor): point(newPoint), color(newColor){};
    ~card();
    int getPoint() const;
    COLOR getColor() const;
};


class cardHeap
{
private:
    queue<card> cards;
public:
    cardHeap();
    ~cardHeap();
    bool isEmpty();
    void initRandom();//initialize a new heap (already constructed) with random order cards
    card& fetchCard();//get a card from the top of the heap
};