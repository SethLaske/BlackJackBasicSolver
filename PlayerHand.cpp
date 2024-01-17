//
// Created by small on 1/16/2024.
//

#include <iostream>
#include "PlayerHand.h"

PlayerHand::PlayerHand(int betSize) {
    this->betSize = betSize;
    canBeSplit = false;
    canBeDoubled = false;
    handFinished = false;
}

PlayerHand::~PlayerHand() {

}



int PlayerHand::getBetSize() const {
    return betSize;
}

void PlayerHand::stay() {
    handFinished = true;
}

void PlayerHand::addCard(const Card& addedCard) {
    Hand::addCard(addedCard);

    //std::cout << "Card is being added to player hand too" << std::endl;

    if(cards.size() == 2){
        canBeDoubled = true;
        if(cards[0].getCardValue() == cards[1].getCardValue()){
            canBeSplit = true;
        }else{
            canBeSplit = false;
        }
    } else{
        canBeDoubled = false;
        canBeSplit = false;
    }

    //These can combine later, this is funnier (and also for testing purposes)
    if(valueCount > 21){
        std::cout << "Bust" << std::endl;
        handFinished = true;
    } else if(valueCount == 21){
        std::cout << "Whats 9 + 10?" << std::endl;
        handFinished = true;
    }
}

void PlayerHand::doubleDown(const Card& addedCard) {
    if(!canBeDoubled){
        return;
    }
    betSize *= 2;
    addCard(addedCard);
    handFinished = true;
}

Card PlayerHand::splitCards() {
    if(!canBeSplit){
        std::cerr << "Can't be split" << std::endl;
        return {Card::SPADES, Card::ACE};
    }
    Card removedCard = cards.back();
    cards.pop_back();

    valueCount -= removedCard.getCardValue();
    //std::cout << "SPLITTING OFF A " << cards[0].getCardValue() << " with a new size of" << cards.size() << std::endl;

    return removedCard;
}

bool PlayerHand::isHandFinished() const {
    return handFinished;
}

int PlayerHand::getHandSize() const {
    return cards.size();
}




