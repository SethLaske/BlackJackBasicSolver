//
// Created by small on 1/16/2024.
//

#include <iostream>
#include "PlayerHand.h"

PlayerHand::PlayerHand(int betSize) {
    this->betSize = betSize;
    canBeSplit = false;
    canBeDoubled = false;
}

PlayerHand::~PlayerHand() {

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
}

float PlayerHand::getBetSize() const {
    return betSize;
}

void PlayerHand::doubleDown(const Card& addedCard) {
    if(!canBeDoubled){
        return;
    }
    betSize *= 2;
    addCard(addedCard);
}

Card PlayerHand::splitCards() {
    if(!canBeSplit){
        std::cerr << "Can't be split" << std::endl;
        return {Card::SPADES, Card::ACE};
    }
    Card removedCard = cards.back();
    cards.pop_back();

    return removedCard;
}


