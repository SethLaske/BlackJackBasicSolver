#include "PlayerBot.h"

PlayerBot::PlayerBot(float startingMoney, StrategyGuideHandler& strategyGuideHandler) : strategyGuideHandler(strategyGuideHandler){
    initialMoney = startingMoney;

    resetStats();
}

PlayerBot::~PlayerBot() {

}

PLAYERACTION PlayerBot::getPlayerAction(PlayerHand &playerHand, const DealerHand &dealerHand) {
    if(playerHand.isHandFinished()){
        return STAY;
    }
    std::string playerCardsString = getPlayerCardDecoding(playerHand);
    std::basic_string<char> strategyRecommendation = strategyGuideHandler.getEntry(playerCardsString , dealerHand.getHandValue());
    return getUseableAction(playerHand, strategyRecommendation);
}

PLAYERACTION PlayerBot::getUseableAction(PlayerHand &playerHand, const std::basic_string<char> &strategyRecommendation) {

    //Leaving room to add functionality for more specifics. For example, adding SplitIfDOS
    if(strategyRecommendation == "Hit"){
        return HIT;
    }

    if (strategyRecommendation == "Stay"){
        return STAY;
    }

    //Adding a second layer of checks for being able to double and split to handle the complexities of a strategy guide
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

    //If the options are ever not provided the hand is shown
    std::cerr << "Couldn't figure out the proper action: " << strategyRecommendation << std::endl;
    playerHand.displayHand();

    return UNKNOWN;
}

std::string PlayerBot::getPlayerCardDecoding(const PlayerHand &playerHand) const {
    std::string playerCardsString;

    if (playerHand.canSplit() && (HouseRules::IGNOREDEBT || money > playerHand.getBetSize())) {
        //Pair of aces would have value of 12, but one ace would be soft
        if (playerHand.getSoftAceCount() > 0) {
            playerCardsString = "S11";
        } else {
            playerCardsString = "S" + std::to_string(playerHand.getHandValue() / 2);
        }
    } else if (playerHand.getSoftAceCount() > 0) {
        //A1 (if can't split aces) to A10
        playerCardsString = "A" + std::to_string(playerHand.getHandValue() - 11);
    } else {
        //If there's no splitting or soft aces, it's just a hard value
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

void PlayerBot::payPlayer(float addedMoney) {
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
}

void PlayerBot::resetStats() {
    money = initialMoney;
    numberOfHandsPlayed = 0;
    numberOfGamesPlayed = 0;

    numberOfDoubles = 0;
    numberOfSplits = 0;

    numberOfTimesPaid = 0;
}

float PlayerBot::getMoney() const {
    return money;
}

float PlayerBot::calculateResults(bool saveToFile) {
    float netProfit = money - initialMoney;
    float profitPerHand = netProfit/numberOfHandsPlayed;

    if(saveToFile){
        strategyGuideHandler.saveResults(profitPerHand);
    }

    return profitPerHand;
}
