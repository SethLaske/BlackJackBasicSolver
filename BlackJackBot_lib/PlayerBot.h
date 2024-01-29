//
// Created by small on 1/16/2024.
//

#ifndef PLAYERBOT_H
#define PLAYERBOT_H


#include "StrategyGuideHandler.h"
#include "PlayerHand.h"
#include "DealerHand.h"
#include "HouseRules.h"

//I am giving the player more control of the player than a casino might typically allow to avoid needing to go back and forth.
//For example, the player will be responsible for ensuring they have money, and doubling only when acceptable

enum PLAYERACTION{
    HIT,
    STAY,
    DOUBLEDOWN,
    SPLIT,
    UNKNOWN
};

class PlayerBot {

public:
    PlayerBot(float startingMoney, StrategyGuideHandler& strategyGuideHandler);
    ~PlayerBot();

    //Logic for player determining the number and size of their bets
    std::vector<int> getPlayerBets(int maxNumberOfBets, int minBet, int maxBet);
    PLAYERACTION getPlayerAction(PlayerHand& playerHand, const DealerHand& dealerHand);

    float getMoney() const;
    void payPlayer(float addedMoney);


    void displayStats() const;
    void resetStats();

    void saveResultsToFile();

private:
    //Variables used for optional data tracking
    float initialMoney;
    float money;

    int numberOfGamesPlayed;
    int numberOfHandsPlayed;

    int numberOfDoubles;
    int numberOfSplits;

    int numberOfTimesPaid;

    StrategyGuideHandler& strategyGuideHandler;

    //Turn the playershand into a string for the strategy guide
    std::string getPlayerCardDecoding(const PlayerHand &playerHand) const;

    //Turn the strategy recommendation into a definitive action
    PLAYERACTION getUseableAction(PlayerHand &playerHand, const std::basic_string<char> &strategyRecommendation);
};


#endif //PLAYERBOT_H
