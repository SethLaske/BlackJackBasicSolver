//
// Created by small on 1/16/2024.
//

#include "Table.h"

#include <utility>

/*Table::Table(PlayerBot& playerBot, Shoe shoe) : playerBot(playerBot), shoe(shoe) {
    //this->playerBot = playerBot;

    //Shoe shoe;


}*/

Table::Table(PlayerBot &playerBot) : playerBot(playerBot), shoe(HouseRules::NUMBEROFDECKSINSHOE, HouseRules::MINPENETRATIONPERCENT, HouseRules::MAXPENETRATIONPERCENT) {

}

Table::~Table() {

}

void Table::runGameTesting(int numberOfGames) {

    shoe.doShuffle();   //force shuffle at start
    dealerHand.clearHand();
    playerHands.clear();

    for(int i = 0; i < numberOfGames; i ++){
        playGame();

        shoe.tryShuffle();


        if(HouseRules::DISPLAYTRIALSPROGRESS) {
            if (numberOfGames > 100 && i % (numberOfGames / HouseRules::TRIALPROGRESSINCREMENTS) == 0) {
                std::cout << (i * 100/numberOfGames) << "% completed with this trial" << std::endl;
            }
        }
    }
    if(HouseRules::DISPLAYRESULTS){
        playerBot.displayStats();
    }
    playerBot.calculateResults(false);

    playerBot.resetStats();
}

void Table::playGame() {
    dealHands();

    if(HouseRules::DISPLAYGAMEINPROGRESS) displayTable();

    handleBlackjacks();



    if(playerHands.empty()){
        if(HouseRules::DISPLAYGAMEINPROGRESS) std::cout << "Game ended due to blackjacks" << std::endl;
        endGame();
        return;
    }

    doAllPlayerHands();

    if(playerHands.empty()){
        if(HouseRules::DISPLAYGAMEINPROGRESS) std::cout << "Game ended due to players busting" << std::endl;
        endGame();
        return;
    }


    getDealerAction();

    if(HouseRules::DISPLAYGAMEINPROGRESS) displayTable();

    int finalDealerValue = dealerHand.getHandValue();



    if(finalDealerValue > 21){
        if(HouseRules::DISPLAYGAMEINPROGRESS) std::cout << "Dealer busted" << std::endl;
        for (PlayerHand& hand : playerHands){
            playerBot.payPlayer((float) hand.getBetSize() * 2);
        }
    }
    else{
        for (PlayerHand& hand : playerHands){
            if(hand.getHandValue() > finalDealerValue){
                payPlayer(hand, 2);
                if(HouseRules::DISPLAYGAMEINPROGRESS) std::cout << "Player win" << std::endl;
            } else if(hand.getHandValue() == finalDealerValue){
                payPlayer(hand, 1);
                if(HouseRules::DISPLAYGAMEINPROGRESS) std::cout << "Player push" << std::endl;
            } else{
                if(HouseRules::DISPLAYGAMEINPROGRESS) std::cout << "Player lose" << std::endl;
            }

        }
    }
    endGame();
}

void Table::endGame() {
    playerHands.clear();
    dealerHand.clearHand();
}

void Table::doAllPlayerHands() {
    std::vector<PlayerHand> remainingPlayerHands;
    while(!playerHands.empty()){

        if(playerHands.front().getHandSize() < 2){
            playerHands.front().addCard(shoe.drawCard());
        }
        getPlayerAction(playerHands.front());
        if(playerHands.front().isHandFinished()){
            if(playerHands.front().getHandValue() <= 21){
                remainingPlayerHands.push_back(playerHands.front());
            }
            playerHands.erase(playerHands.begin());
        }
    }

    playerHands = remainingPlayerHands;
}

void Table::dealHands() {

    int maxNumberOfBets = 2;
    int minBet = 10;
    int maxBet = 500;

    //Create a hand for all the players created
    for (int bet : playerBot.getPlayerBets(maxNumberOfBets, minBet, maxBet)) {
        PlayerHand playerHand(bet);
        playerHands.push_back(playerHand);
    }

    //Its randomized each time, but still dealing from shoe in proper order
    for (PlayerHand& hand : playerHands){
        hand.addCard(shoe.drawCard());

    }
    dealerHand.addHiddenCard(shoe.drawCard());
    for (PlayerHand& hand : playerHands){
        hand.addCard(shoe.drawCard());

    }
    dealerHand.addCard(shoe.drawCard());
}

void Table::handleBlackjacks(){
    if(dealerHand.isBlackJack()){
        for(PlayerHand hand : playerHands){
            if(hand.isBlackJack()){
                payPlayer(hand, 1);
            }
        }
        playerHands.clear();
        return;
    }

    float blackJackPayout = HouseRules::BLACKJACKPAYOUTRATE + 1;    // 3:2 + 1
    std::vector<PlayerHand> unfinishedPlayerHands;
    for(PlayerHand hand : playerHands){
        if(hand.isBlackJack()){

            payPlayer(hand, blackJackPayout);
        }else{
            unfinishedPlayerHands.push_back(hand);
        }
    }
    playerHands.clear();
    playerHands = unfinishedPlayerHands;
}

void Table::payPlayer(const PlayerHand &playerHand, float payoutRate) {

    playerBot.payPlayer((float) playerHand.getBetSize() * payoutRate);

}

void Table::getPlayerAction(PlayerHand &playerHand) {
    PLAYERACTION action = playerBot.getPlayerAction(playerHand, dealerHand);

    switch (action) {
        case(PLAYERACTION::STAY):
        case(PLAYERACTION::UNKNOWN):
            playerHand.stay();
            break;

        case(PLAYERACTION::HIT):
            playerHand.addCard(shoe.drawCard());
            break;
        case(PLAYERACTION::DOUBLEDOWN):
            playerHand.doubleDown(shoe.drawCard());
            break;
        case(PLAYERACTION::SPLIT):
            Card splitCard = playerHand.splitCards();
            playerHands.push_back(PlayerHand(playerHand.getBetSize()));  // Create a new PlayerHand with the same bet size
            playerHands.back().addCard(splitCard);  // Add the splitCard to the new PlayerHand

            break;

            //I have no idea why I can't add a default here
        //default:
          //  std::cerr << "Fucking dumbass" << std::endl;
            //break;
    }
}

void Table::getDealerAction() {
    dealerHand.revealHiddenCard();

    //Should be permanent dealer rules, hit until 17 or soft 17
    while (dealerHand.getHandValue() < 17 || (dealerHand.getHandValue() == 17 && dealerHand.getSoftAceCount() > 0)){
        dealerHand.addCard(shoe.drawCard());
    }
}

void Table::displayTable() {
    std::cout << "---------------------------" << std::endl;
    dealerHand.displayHand();
    for(PlayerHand player: playerHands){
        player.displayHand();
    }
    std::cout << "---------------------------" << std::endl;
}




