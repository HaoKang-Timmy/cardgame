#include<iostream>
#include "card.h"
#include "player.h"
using namespace std;
int main()
{
    int playern;
    char judge;
    cout<<"Please input number of player:\n";
    cin>>playern;
    const int playernum=playern;
    player array_player[playernum];
    cardHeap playing_heap;
    playing_heap.initRandom();
    while(1)
    {
        for(int i=0;i<playernum;i++)
        {
            array_player[i].set_round(1);
            while(1)
            {
                cin>>judge;
                if(judge=='y')
                {
                    array_player[i].player_fetchCard(playing_heap.fetchCard());
                    cout<<"player"<< i <<"score:"<<array_player[i].get_score()<<endl;
                    if(array_player[i].get_score()>=21)
                        break;
                }
                else if(judge=='n')
                    break;
                else 
                    break;
            }
            if(judge=='q')
                break;



        }
    }
}
