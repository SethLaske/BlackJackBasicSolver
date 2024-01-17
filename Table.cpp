//
// Created by small on 1/16/2024.
//

#include "Table.h"

Table::Table(PlayerBot playerBot) : playerBot(playerBot) {
    this->playerBot = playerBot;

    //Shoe shoe;


}

Table::~Table() {

}

void Table::startGame() {
    dealHands();
    handleBlackjacks();

    if(playerHands.empty()){
        std::cout << "No players remaining due to blackjacks" << std::endl;
        return;
    }

    doAllPlayerHands();

    if(playerHands.empty()){
        std::cout << "No players remaining due to a bunch of NNN fails" << std::endl;
        return;
    }

    std::cout << "Reached Dealer Logic" << std::endl;

    getDealerAction();

    int finalDealerValue = dealerHand.getHandValue();

    std::cout << "Dealer finished with a " << finalDealerValue << std::endl;

    if(finalDealerValue > 21){
        std::cout << "Dealer Bust, Table Win" << std::endl;
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
                std::cout << "L" << std::endl;
            }

        }
    }

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
                std::cout << "Bro could have hit one more time" << std::endl;
            }
            playerHands.erase(playerHands.begin());
        }
    }

    playerHands = remainingPlayerHands;
}

void Table::dealHands() {

    //playerBot
    int maxNumberOfBets = 2;
    int minBet = 5;
    int maxBet = 500;

    //Create a hand for all the players created
    for (int bet : playerBot.getPlayerBets(maxNumberOfBets, minBet, maxBet)) {
        PlayerHand playerHand(bet);
        playerHands.push_back(playerHand);
    }

    for (PlayerHand& hand : playerHands){
        hand.addCard(shoe.drawCard());
        //hand.addCard(Card(Card::SPADES, Card::TEN));
    }
    dealerHand.dealHiddenCard(shoe.drawCard());
    for (PlayerHand& hand : playerHands){
        hand.addCard(shoe.drawCard());
        //hand.addCard(Card(Card::SPADES, Card::ACE));
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
        std::cout << "The dealer hit blackjack, the game is over" << std::endl;
        playerHands.clear();
        return;
    }

    float blackJackPayout = 1.5 + 1;    // 3:2 + 1
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
        std::cout << "Player pushed" << std::endl;
    } else if(payoutRate == 2){
        std::cout << "Player won" << std::endl;
    } else{
        std::cout << "Player blackjack" << std::endl;
    }
    playerBot.getPaid((float)playerHand.getBetSize() * payoutRate);

}

void Table::getPlayerAction(PlayerHand &playerHand) {
    PLAYERACTION action = playerBot.getPlayerAction(playerHand, dealerHand);

    switch (action) {
        case(PLAYERACTION::STAY):
            playerHand.stay();
            break;
        case(PLAYERACTION::HIT):
            playerHand.addCard(shoe.drawCard());
            break;
        case(PLAYERACTION::DOUBLE):
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
        std::cout << "The dealer hits resulting in a " << dealerHand.getHandValue() <<std::endl;
    }
}
