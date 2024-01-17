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
        //hand.addCard(shoe.drawCard());
        hand.addCard(Card(Card::SPADES, Card::TEN));
    }
    dealerHand.dealHiddenCard(shoe.drawCard());
    for (PlayerHand& hand : playerHands){
        //hand.addCard(shoe.drawCard());
        hand.addCard(Card(Card::SPADES, Card::ACE));
    }
    dealerHand.addCard(shoe.drawCard());

    if(dealerHand.isBlackJack()){
        for(PlayerHand hand : playerHands){
            if(hand.isBlackJack()){
                payPlayer(hand, 1);
            }
        }
        std::cout << "The dealer hit blackjack, the game is over" << std::endl;
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

    if(playerHands.empty()){
        std::cout << "No players remaining" << std::endl;
    }


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
