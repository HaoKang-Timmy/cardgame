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
    cout<<"input y for continue fetch cards, n or other words to for another's round, q for quit"<<endl;
    const int playernum=playern;
    player array_player[playernum];
    cardHeap playing_heap;
    playing_heap.initRandom();
    while(1)
    {
        for(int i=0;i<playernum;i++)
        {
            array_player[i].set_round(1);
            cout<<"player "<<i+1<<" round begin!"<<endl;
            while(1)
            {
                cin>>judge;
                if(judge=='y')
                {
                    array_player[i].player_fetchCard(playing_heap.fetchCard());
                    cout<<"player"<< i <<"score:"<<array_player[i].get_score()<<endl;
                    if(array_player[i].get_score()>=21)
                        break;
                    if(playing_heap.isEmpty())
                    {
                        playing_heap.initRandom();
                    }
                }
                else if(judge=='n')
                    break;
                else 
                    break;
            }
            if(judge=='q')
                goto outof;




        }
        int max_id=0;
        int flag=0;
        for(int i=0;i<playernum-1;i++)
        {
            if(array_player[i].get_score()>array_player[i+1].get_score() && array_player[i].get_score()<=21)
            {
                flag=1;
                max_id=i;
            }
        }
        if(flag)
        {
            cout<<max_id+1<<"win !"<<endl;
        }
        else 
            cout<<"all loses!"<<endl;
        
        for(int i=0;i<playernum;i++)
        {
            array_player[i].init_player();
        }
    }
outof:
    return 1;
}
