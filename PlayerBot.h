//
// Created by small on 1/16/2024.
//

#ifndef PLAYERBOT_H
#define PLAYERBOT_H


#include "StrategyGuideHandler.h"
#include "PlayerHand.h"
#include "DealerHand.h"

//I am giving the player more control of the player than a casino might typically allow to avoid needing to go back and forth.
//For example, the player will be responsible for ensuring they have money, and doubling only when acceptable

enum PLAYERACTION{
    HIT,
    STAY,
    DOUBLE,
    SPLIT
};

class PlayerBot {

public:
    PlayerBot(float startingMoney, const StrategyGuideHandler& strategyGuideHandler);
    ~PlayerBot();

    std::vector<int> getPlayerBets(int maxNumberOfBets, int minBet, int maxBet);
    PLAYERACTION getPlayerAction(PlayerHand& playerHand, const DealerHand& dealerHand);

    void getPaid(float addedMoney);
    float money;

    void displayStats();

private:
    float initialMoney;

    int numberOfGamesPlayed;
    int numberOfHandsPlayed;

    int numberOfDoubles;
    int numberOfSplits;

    int numberOfTimesPaid;

    StrategyGuideHandler strategyGuideHandler;
};


#endif //PLAYERBOT_H
