//
// Created by small on 1/16/2024.
//

#ifndef TABLE_H
#define TABLE_H

#include "PlayerBot.h"
#include "DealerHand.h"
#include "PlayerHand.h"
#include "Shoe.h"

class Table {

public:
    Table(PlayerBot playerBot); //House Rules when I get to it
    ~Table();

    void startGame();

private:
    Shoe shoe;
    PlayerBot playerBot;
    DealerHand dealerHand;
    std::vector<PlayerHand> playerHands;    //Sadly in order to split I need to include it from the start
    //House Rules


    void dealHands();

    void payPlayer(const PlayerHand& playerHand, float payoutRate);     //1 for push, 2 for win, blackjack payout + 1 for natural blackjack

    void hitHand(Hand& hand);
    void stayHand(Hand& hand);
    //Dealer can never double or split
    void doubleHand(PlayerHand& hand);
    void splitHand(PlayerHand& hand);

    void getPlayerAction(PlayerHand& playerHand);
    void getDealerAction(DealerHand& dealerHand);
};


#endif //TABLE_H
