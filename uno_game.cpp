#include "uno_game.h"
#include "ui_uno_game.h"
#include "include/card.h"
#include "qtimer.h"
#include <QMessageBox>

uno_game::uno_game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uno_game)
{
    ui->setupUi(this);
    game_init();
}


uno_game::~uno_game()
{
    delete ui;
}

/**
 * @brief do any preparations for the game, involving frontend and backend
 */
void uno_game::game_init()
{
    //initiate players
    players[0] = new player_uno(true);
    players[1] = new player_uno(false);
    players[2] = new player_uno(false);
    players[3] = new player_uno(false);

    //initiate the public card heap
    public_cards.init_random();
    for(int i = 0; i < public_cards.get_size(); i++) public_cards[i]->setProcesser(-1);
    qDebug()<<public_cards.get_size();

    //randomly give each player 7 cards
    for(int j = 0; j < 4; j++)
    {
        player_fetch_card(j, 7);
    }

    //fetch the top card (not wild) from the rest of cards (won't remove it) to let it be the start card
    int i = 0;
    while(i < public_cards.get_size() && public_cards[i]->getColor() == card_uno::BLACK) i++;
    last_card = public_cards[i];

    //initiate the cards display
    player_card_list[0] = ui->mycard0;
    player_card_list[1] = ui->mycard1;
    player_card_list[2] = ui->mycard2;
    player_card_list[3] = ui->mycard3;
    player_card_list[4] = ui->mycard4;
    player_card_list[5] = ui->mycard5;
    player_card_list[6] = ui->mycard6;
    player_card_list[7] = ui->mycard7;
    player_card_list[8] = ui->mycard8;
    player_card_list[9] = ui->mycard9;
    player_card_list[10] = ui->mycard10;
    player_card_list[11] = ui->mycard11;
    player_card_list[12] = ui->mycard12;
    player_card_list[13] = ui->mycard13;
    player_card_list[14] = ui->mycard14;
    player_card_button_list[0] = ui->button_card0;
    player_card_button_list[1] = ui->button_card1;
    player_card_button_list[2] = ui->button_card2;
    player_card_button_list[3] = ui->button_card3;
    player_card_button_list[4] = ui->button_card4;
    player_card_button_list[5] = ui->button_card5;
    player_card_button_list[6] = ui->button_card6;
    player_card_button_list[7] = ui->button_card7;
    player_card_button_list[8] = ui->button_card8;
    player_card_button_list[9] = ui->button_card9;
    player_card_button_list[10] = ui->button_card10;
    player_card_button_list[11] = ui->button_card11;
    player_card_button_list[12] = ui->button_card12;
    player_card_button_list[13] = ui->button_card13;
    player_card_button_list[14] = ui->button_card14;
    update_player_card_display();
    update_last_card_display();
    card_uno temp;//other cards (only display the back side)
    temp.set_picture(":/uno_cards/graph/uno_cards/Cardback.png");
    update_card_display(ui->label_19, &temp, 1);
    update_card_display(ui->label_20, &temp, 1);
    update_card_display(ui->label_21, &temp, 1);
    update_card_display(ui->label_22, &temp, 1);
    update_card_display(ui->label_23, &temp, 1);
    update_card_display(ui->label_24, &temp, 1);
    update_card_display(ui->label_38, &temp, 1);
    update_card_display(ui->label_32, &temp, -1);
    update_card_display(ui->label_33, &temp, -1);
    update_card_display(ui->label_34, &temp, -1);
    update_card_display(ui->label_35, &temp, -1);
    update_card_display(ui->label_36, &temp, -1);
    update_card_display(ui->label_37, &temp, -1);
    update_card_display(ui->label_39, &temp, -1);
    update_card_display(ui->label_25, &temp, false);
    update_card_display(ui->label_26, &temp, false);
    update_card_display(ui->label_27, &temp, false);
    update_card_display(ui->label_28, &temp, false);
    update_card_display(ui->label_29, &temp, false);
    update_card_display(ui->label_30, &temp, false);
    update_card_display(ui->label_31, &temp, false);
    update_card_display(ui->label_18, &temp, false);

    //display the direction
    update_direction_display();

    //display the indicator of the current player
    current_player_indicator[0] = ui->current_is_player;
    current_player_indicator[1] = ui->current_is_robot1;
    current_player_indicator[2] = ui->current_is_robot2;
    current_player_indicator[3] = ui->current_is_robot3;
    ui->current_is_robot1->setHidden(true);
    ui->current_is_robot2->setHidden(true);
    ui->current_is_robot3->setHidden(true);


    m_timer = new QTimer(this);
    this->connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTiming()));
    m_timer->start(2000);
}

void uno_game::slotTiming()
{
    if(current_player != 0) {
        qDebug()<<current_player;
        card_uno *card = players[current_player]->ai_chosen(last_card,direction_is_clockwise,draw_card_number_accumulate);
        if(card) {
            qDebug()<<"fetch card";
            player_give_card(current_player, card);
            players[current_player]->give_card(card);
        }
        else {
            qDebug()<<"no card";
            player_fetch_card(current_player, 2);
            go_on_to_the_next_player();
        }
    }
}

/**
 * @brief randomly fetch a specified number of cards from the public heap and add them to the player's card heap
 * @param player_index the index of the player
 * @param numcard the number of cards to fetch
 */
void uno_game::player_fetch_card(int player_index, int numcard)
{
    if(!(player_index >= 0) || !(player_index < 4)) return;//handle illegal index
    card_uno *card;
    for(int i = 0; i < numcard && public_cards.get_size() > 0; i++)
    {//the number of the cards to fetch also depends on whether there are enough cards in the heap
        card = public_cards.random_fetch_card();
        //qDebug()<<public_cards.get_size();
        card->setProcesser(player_index);
        players[player_index]->fetch_card(card);
    }
}

/**
 * @brief a private function to change the card picture of a card label in UI
 * @param card_display the label pointer
 * @param card the new card pointer
 * @param rotate_90 0 for don't rotate, 1 for rotate clockwise, -1 for rotate anticlockwise
 */
void uno_game::update_card_display(QLabel *card_display, card_uno *card, int rotate_90)
{
    card_display->setStyleSheet("background-color: rgba(0, 0, 0, 0);");//clear any previous thing
    if(card)
    {
        if(rotate_90)
        {
            QTransform trans;
            if(rotate_90 == 1) trans.rotate(90);
            else trans.rotate(-90);
            card_display->setPixmap(card->getPicture().transformed(trans,Qt::SmoothTransformation));
        }
        else card_display->setPixmap(card->getPicture());
    }
    else
    {
        QPixmap blank = QPixmap();
        card_display->setPixmap(blank);
    }
}

/**
 * @brief update the human player's cards displayed on the UI
 */
void uno_game::update_player_card_display()
{
    player_cards_mapping.clear();
    for(int i = 0; i < 15; i++)
    {
        if(i < players[0]->get_current_card_number())
        {
            update_card_display(player_card_list[i], players[0]->peek_card(i), false);
            player_cards_mapping[player_card_list[i]] = players[0]->peek_card(i);
            player_card_button_list[i]->setHidden(false);
        }
        else
        {
            update_card_display(player_card_list[i], nullptr, false);
            player_cards_mapping[player_card_list[i]] = nullptr;
            player_card_button_list[i]->setHidden(true);
        }
    }
}

/**
 * @brief update the last card given out displayed on UI
 */
void uno_game::update_last_card_display()
{
    update_card_display(ui->lastcard, last_card, false);
}

/**
 * @brief update the logo indicating the direction on UI
 */
void uno_game::update_direction_display()
{
    ui->direction->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    QPixmap map;
    map.load(":/uno_cards/direction/graph/uno_cards/direction/" + QString::number(static_cast<int>(direction_is_clockwise)) + ".png");
    ui->direction->setPixmap(map.scaled(111, 111, Qt::KeepAspectRatio));
}

/**
 * @brief change the direction
 */
void uno_game::reverse()
{
    direction_is_clockwise = !direction_is_clockwise;
    update_direction_display();
}

/**
 * @brief Move on to the next player. Auto fetch card for the player if the player have no card to give out.
 */
void uno_game::go_on_to_the_next_player()
{
    if(direction_is_clockwise)
    {
        if(!skip_flag)
            current_player = (current_player + 1) % 4;
        else
            current_player = (current_player + 2) % 4;
    }
    else
    {
        if(!skip_flag)
            current_player = (current_player + 3) % 4;// 3 mod 4 == -1 mod 4
        else
            current_player = (current_player + 2) % 4;
    }
    for(int i = 0; i < 4; i++)
    {
        if(i == current_player) current_player_indicator[i]->setHidden(false);
        else current_player_indicator[i]->setHidden(true);
    }
    skip_flag = false;
    if(players[current_player]->no_cards_to_give(last_card))
    {
        player_fetch_card(current_player, 2);
        go_on_to_the_next_player();
    }
}

/**
 * @brief the slot for the button "结束游戏"
 */
void uno_game::on_end_clicked()
{
    this->close();
    w1->show();
}

/**
 * @brief put the card given out by player into the public heap, if the card doesn't satisfy the condition then draw cards for the player
 *        玩家出牌的逻辑是：点到相应的牌之后先是slot函数响应，获得该牌的指针，并把牌从玩家的牌堆中移出，再以该指针为参数调用本函数；之后，本函数将牌放入公共牌堆里，并检查这张牌是否符合要求，
 *        如果不符合要求，就自动给玩家抽一张牌（调用的函数会直接将牌放进玩家的牌堆），此时有功能的牌功能不起作用；
 *        如果符合要求，该情况下如果牌是功能牌，功能就起作用。
 *        之后本函数会检查该玩家是否还有牌，如果没有，直接指出游戏结束，该玩家获胜；
 *        反之，会调用相应的函数将当前的出牌玩家变成下一个玩家。
 * @param player_index the index of the player
 * @param card the pointer to the card given by the player
 */
void uno_game::player_give_card(int player_index, card_uno *card)
{
    qDebug()<<card->getColor()<<card->getCardType();
    if(!(player_index >= 0) || !(player_index < 4)) return;
    if(!card->this_card_give_OK(last_card))
    {
        if(draw_card_number_accumulate > 0)
        {
            player_fetch_card(player_index, draw_card_number_accumulate);
            draw_card_number_accumulate = 0;
        }
        else player_fetch_card(player_index, 1);
    }
    else
    {
        if(card->getCardType() == card_uno::WILD)
        {

        }
        else if(card->getCardType() == card_uno::WILD_DRAW_FOUR)
        {
            draw_card_number_accumulate += 4;
        }
        else if(card->getCardType() == card_uno::REVERSE)
        {
            reverse();
        }
        else if(card->getCardType() == card_uno::SKIP) skip_flag = true;
        else if(card->getCardType() == card_uno::DRAW_TWO) draw_card_number_accumulate += 2;
    }
    card->setProcesser(-1);
    public_cards.insert_card(card);
    last_card = card;
    update_player_card_display();
    update_last_card_display();
    if(players[player_index]->win())
    {
        if(player_index)
            QMessageBox::information(this, "游戏结束！", "Robot" + QString::number(player_index) + "获胜！");
        else
            QMessageBox::information(this, "游戏结束！", "您获胜了！");
        this->close();
        w1->show();
    }
    go_on_to_the_next_player();
}

//below are the slot functions of the card buttons.
//the card (if exist) will be give out if corresponding button clicked
void uno_game::on_button_card0_clicked()
{
    //qDebug()<<"card0 clicked";
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard0]);
    if(card) player_give_card(0, card);
}

void uno_game::on_button_card1_clicked()
{
    //qDebug()<<"card1 clicked";
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard1]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card2_clicked()
{
    //qDebug()<<"card2 clicked";
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard2]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card3_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard3]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card4_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard4]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card5_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard5]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card6_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard6]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card7_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard7]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card8_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard8]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card9_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard9]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card10_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard10]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card11_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard11]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card12_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard12]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card13_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard13]);
    if(card) player_give_card(0, card);
}


void uno_game::on_button_card14_clicked()
{
    if(current_player != 0) return;//only react when it's the human player's turn
    card_uno *card = players[0]->give_card(player_cards_mapping[ui->mycard14]);
    if(card) player_give_card(0, card);
}

