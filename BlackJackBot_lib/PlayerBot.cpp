//
// Created by small on 1/16/2024.
//

#include "PlayerBot.h"

PlayerBot::PlayerBot(float startingMoney, StrategyGuideHandler& strategyGuideHandler) : strategyGuideHandler(strategyGuideHandler){
    initialMoney = startingMoney;

    //this->strategyGuideHandler = strategyGuideHandler;

    resetStats();
}

PlayerBot::~PlayerBot() {
    //std::cout << "The players final money was " << money << std::endl;
}

PLAYERACTION PlayerBot::getPlayerAction(PlayerHand &playerHand, const DealerHand &dealerHand) {
    std::string playerCardsString = getPlayerCardDecoding(playerHand);

    std::basic_string<char> strategyRecommendation = strategyGuideHandler.getEntry(playerCardsString , dealerHand.getHandValue());

    return getUseableAction(playerHand, strategyRecommendation);
}

PLAYERACTION PlayerBot::getUseableAction(PlayerHand &playerHand, const std::basic_string<char> &strategyRecommendation) {
    if(strategyRecommendation == "Hit"){
        return HIT;
    }

    if (strategyRecommendation == "Stay"){
        return STAY;
    }

    if (strategyRecommendation == "Double"){
        if(playerHand.canDouble() && (HouseRules::IGNOREDEBT || money > playerHand.getBetSize())){
            money -= playerHand.getBetSize();
            numberOfDoubles++;
            return DOUBLEDOWN;
        }
        return HIT;
    }

    if (strategyRecommendation == "Split"){
        if(playerHand.canSplit() && (HouseRules::IGNOREDEBT || money > playerHand.getBetSize())){
            money -= playerHand.getBetSize();
            numberOfSplits++;
            return SPLIT;
        }

        return STAY;
    }

    std::cerr << strategyRecommendation << "Couldn't figure out the proper move" << std::endl;
    playerHand.displayHand();

    return UNKNOWN;
}

std::string PlayerBot::getPlayerCardDecoding(const PlayerHand &playerHand) const {
    std::string playerCardsString;

    if (playerHand.canSplit() && (HouseRules::IGNOREDEBT || money > playerHand.getBetSize())) {
        if (playerHand.getSoftAceCount() > 0) {
            playerCardsString = "S11";
        } else {
            // Assuming getHandValue() returns an integer
            playerCardsString = "S" + std::to_string(playerHand.getHandValue() / 2);
        }
    } else if (playerHand.getSoftAceCount() > 0) {
        // Assuming getHandValue() returns an integer
        playerCardsString = "A" + std::to_string(playerHand.getHandValue() - 11);
    } else {
        // Assuming getHandValue() returns an integer
        playerCardsString = std::to_string(playerHand.getHandValue());
    }
    return playerCardsString;
}

std::vector<int> PlayerBot::getPlayerBets(int maxNumberOfBets, int minBet, int maxBet) {
    //Too soon to deal with analyzing bet sizes
    std::vector<int> bets = {minBet};

    for(int bet : bets){
        money -= (float) bet;
        numberOfHandsPlayed ++;
    }
    numberOfGamesPlayed ++;

    return bets;
}

void PlayerBot::getPaid(float addedMoney) {
    numberOfTimesPaid++;
    money += addedMoney;
}

void PlayerBot::displayStats() const {
    float netProfit = money - initialMoney;
    float profitPerGame = netProfit/numberOfGamesPlayed;
    float profitPerHand = netProfit/numberOfHandsPlayed;

    std::cout << "********************************" << std::endl;
    std::cout << "PLAYER RECAP" << std::endl;
    std::cout << "Initial -> Final" << std::endl;
    std::cout << initialMoney << " -> " << money << std::endl;
    std::cout << "Hands Played / Games Played" << std::endl;
    std::cout << numberOfHandsPlayed << " / " << numberOfGamesPlayed << std::endl;
    std::cout << "Doubles : Splits" << std::endl;
    std::cout << numberOfDoubles << " : " << numberOfSplits << std::endl;
    std::cout << "Net Profit " << netProfit << std::endl;
    std::cout << "Profit per Game: " << profitPerGame << std::endl;
    std::cout << "Profit per Hand " << profitPerHand << std::endl;
    std::cout << "Number of loses " << (numberOfHandsPlayed - numberOfTimesPaid) << std::endl;
    //std::cout << "House edge " << (numberOfHandsPlayed - numberOfTimesPaid) << std::endl;
    std::cout << "********************************" << std::endl;

    //strategyGuideHandler.saveResults(profitPerHand);
}

void PlayerBot::resetStats() {
    money = initialMoney;
    numberOfHandsPlayed = 0;
    numberOfGamesPlayed = 0;

    numberOfDoubles = 0;
    numberOfSplits = 0;

    numberOfTimesPaid = 0;
}

void PlayerBot::saveResults() {
    float netProfit = money - initialMoney;
    float profitPerHand = netProfit/numberOfHandsPlayed;
    strategyGuideHandler.saveResults(profitPerHand);
}

float PlayerBot::getMoney() const {
    return money;
}
