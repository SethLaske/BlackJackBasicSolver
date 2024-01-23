//
// Created by small on 1/16/2024.
//

#include "Table.h"

#include <utility>

Table::Table(const PlayerBot& playerBot, Shoe shoe) : playerBot(playerBot), shoe(std::move(shoe)) {
    //this->playerBot = playerBot;

    //Shoe shoe;


}

Table::Table(const PlayerBot &playerBot) : playerBot(playerBot), shoe(HouseRules::NUMBEROFDECKSINSHOE, HouseRules::MINPENETRATIONPERCENT, HouseRules::MAXPENETRATIONPERCENT) {
    //this->playerBot = playerBot;
    //std::cout << "The number of decks is: " << shoe.getNumberOfDecks() << std::endl;
}

Table::~Table() {

}

void Table::runGameTesting(int numberOfGames) {



    for(int i = 0; i < numberOfGames; i ++){
        startGame();
        endGame();
        shoe.tryShuffle();

        //std::cout<< "******" << i << std::endl;
        //if(numberOfGames > 100 && i % (numberOfGames/20) == 0){
        //    std::cout<< "There should be 20 of these" << std::endl;
        //}
    }
    //std::cout<< "player bot?" << std::endl;
    playerBot.displayStats();
}

void Table::startGame() {
    dealHands();

    //displayTable();
    handleBlackjacks();

    if(playerHands.empty()){
        //std::cout << "No players remaining due to blackjacks" << std::endl;
        return;
    }

    doAllPlayerHands();

    if(playerHands.empty()){
        //std::cout << "No players remaining due to a bunch of NNN fails" << std::endl;
        return;
    }

    //std::cout << "Reached Dealer Logic" << std::endl;

    getDealerAction();

    //displayTable();

    int finalDealerValue = dealerHand.getHandValue();

    //std::cout << "Dealer finished with a " << finalDealerValue << std::endl;

    if(finalDealerValue > 21){
        //std::cout << "Dealer Bust, Table Win" << std::endl;
        for (PlayerHand& hand : playerHands){
            playerBot.getPaid((float) hand.getBetSize() * 2);
        }
    }
    else{
        for (PlayerHand& hand : playerHands){
            if(hand.getHandValue() > finalDealerValue){
                payPlayer(hand, 2);
            } else if(hand.getHandValue() == finalDealerValue){
                payPlayer(hand, 1);
            } else{
                //std::cout << "L" << std::endl;
            }

        }
    }

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
                //std::cout << "Bro could have hit one more time" << std::endl;
            }
            playerHands.erase(playerHands.begin());
        }
    }

    playerHands = remainingPlayerHands;
}

void Table::dealHands() {

    //playerBot
    int maxNumberOfBets = 2;
    int minBet = 10;
    int maxBet = 500;

    //Create a hand for all the players created
    for (int bet : playerBot.getPlayerBets(maxNumberOfBets, minBet, maxBet)) {
        PlayerHand playerHand(bet);
        playerHands.push_back(playerHand);
    }

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
        //std::cout << "The dealer hit blackjack, the game is over" << std::endl;
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

    if(payoutRate == 1){
        //std::cout << "Player pushed" << std::endl;
    } else if(payoutRate == 2){
        //std::cout << "Player won" << std::endl;
    } else{
        //std::cout << "Player blackjack" << std::endl;
    }
    playerBot.getPaid((float)playerHand.getBetSize() * payoutRate);

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

        //default:
          //  std::cerr << "Fucking dumbass" << std::endl;
            //break;
    }
}

void Table::getDealerAction() {
    dealerHand.revealHiddenCard();

    while (dealerHand.getHandValue() < 17 || (dealerHand.getHandValue() == 17 && dealerHand.getSoftAceCount() > 0)){
        dealerHand.addCard(shoe.drawCard());
        //std::cout << "The dealer hits resulting in a " << dealerHand.getHandValue() <<std::endl;
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




