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
    //Table(PlayerBot& playerBot, Shoe shoe);
    Table(PlayerBot& playerBot);
    ~Table();

    //Repeats games, shuffling until finished
    float runGameTesting(int numberOfGames);
    //Plays a single game
    void playGame();

private:
    Shoe shoe;
    PlayerBot& playerBot;
    DealerHand dealerHand;
    std::vector<PlayerHand> playerHands;

    //Individual parts of the game
    void dealHands();
    void handleBlackjacks();
    void doAllPlayerHands();
    void getPlayerAction(PlayerHand& playerHand);
    void getDealerAction();
    void endGame();

    void payPlayer(const PlayerHand& playerHand, float payoutRate);     //1 for push, 2 for win, blackjack payout + 1 for natural blackjack

    void displayTable();
};


#endif //TABLE_H
