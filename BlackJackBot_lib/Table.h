//
// Created by small on 1/16/2024.
//

#ifndef TABLE_H
#define TABLE_H

#include "PlayerBot.h"
#include "DealerHand.h"
#include "PlayerHand.h"
#include "Shoe.h"
#include "HouseRules.h"

class Table {

public:
    Table(PlayerBot& playerBot, Shoe shoe);
    Table(PlayerBot& playerBot);
    ~Table();

    void runGameTesting(int numberOfGames);
    void startGame();
    void endGame();

private:
    Shoe shoe;
    PlayerBot& playerBot;
    DealerHand dealerHand;
    std::vector<PlayerHand> playerHands;    //Sadly in order to split I need to include it from the start
    //House Rules


    void dealHands();
    void handleBlackjacks();
    void doAllPlayerHands();

    void payPlayer(const PlayerHand& playerHand, float payoutRate);     //1 for push, 2 for win, blackjack payout + 1 for natural blackjack

    void getPlayerAction(PlayerHand& playerHand);
    void getDealerAction();

    void displayTable();

};


#endif //TABLE_H
