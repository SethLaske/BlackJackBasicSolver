//
// Created by small on 1/16/2024.
//

#include "PlayerBot.h"

PlayerBot::PlayerBot(float startingMoney, const StrategyGuideHandler& strategyGuideHandler) {
    money = startingMoney;
    this->strategyGuideHandler = strategyGuideHandler;


}

PlayerBot::~PlayerBot() {

}

PLAYERACTION PlayerBot::getPlayerAction(const PlayerHand &playerHand, const DealerHand &dealerHand) {

    /*std::ostringstream playerCardsStream;
    if(playerHand.canBeSplit && money >= playerHand.getBetSize()){
        if(playerHand.getSoftAceCount() > 0){
            playerCardsStream << "S11";
        }else{
            playerCardsStream << "S" << playerHand.getHandValue()/2;
        }
    }

    else if(playerHand.getSoftAceCount() > 0){
        playerCardsStream << "A" << playerHand.getHandValue()-11;
    }

    else {
        playerCardsStream << playerHand.getHandValue();
    }*/

    std::string playerCardsString;

    if (playerHand.canBeSplit && money >= playerHand.getBetSize()) {
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

    //playerCardsString = "Fuck you";

    std::basic_string<char> strategyRecommendation = strategyGuideHandler.getEntry(playerCardsString , dealerHand.getHandValue());

    std::cout << "I have a: " << playerHand.getHandValue() << " which results in a: " << playerCardsString << " against the dealers " << dealerHand.getHandValue() << " So I will " << strategyRecommendation;

    if(strategyRecommendation == "Hit"){
        return PLAYERACTION::HIT;
    } else if (strategyRecommendation == "Stay"){
        return PLAYERACTION::STAY;
    } else if (strategyRecommendation == "Double"){
        if(playerHand.canBeDoubled && money > playerHand.getBetSize()){
            money -= playerHand.getBetSize();
            return PLAYERACTION::DOUBLE;
        }
        return PLAYERACTION::HIT;
    } else if (strategyRecommendation == "Split"){
        if(playerHand.canBeSplit && money > playerHand.getBetSize()){
            money -= playerHand.getBetSize();
            return PLAYERACTION::SPLIT;
        }

        return PLAYERACTION::STAY;
    }

    std::cerr << "Couldn't figure out the proper move so Im hitting like a man";
    return HIT;
}

std::vector<int> PlayerBot::getPlayerBets(int maxNumberOfBets, int minBet, int maxBet) {
    //Too soon to deal with analyzing bet sizes
    return {minBet, maxBet};
}

void PlayerBot::getPaid(float addedMoney) {
    money += addedMoney;
}
