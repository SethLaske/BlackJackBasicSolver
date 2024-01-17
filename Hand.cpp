//
// Created by small on 1/16/2024.
//

#include <iostream>
#include "Hand.h"

Hand::Hand() {
    valueCount = 0;
    softAceCount = 0;
}

Hand::~Hand() {

}

void Hand::addCard(const Card& addedCard) {

    cards.push_back(addedCard);

    //std::cout << "The card being added to the hand is the " << addedCard.toString() << " with a value of: " << addedCard.getCardValue() << std::endl;
    if(addedCard.getCardValue() == 11){
        softAceCount ++;
    }

    valueCount += addedCard.getCardValue();

    //std::cout << "The current value of the hand is "<< valueCount << std::endl;

    if(valueCount > 21 && softAceCount > 0){
        valueCount -= 10;
        softAceCount--;
    }


}

bool Hand::isBlackJack() {
    //std::cout << "Checking for natural blackjack" << std::endl;
    if(cards.size() != 2){
        //std::cout << "size is not 2, it is: " << cards.size() <<std::endl;
        return false;
    }
    if(valueCount == 21){
        return true;
    }
    return false;
}

int Hand::getHandValue() const {
    return valueCount;
}

int Hand::getSoftAceCount() const {
    return softAceCount;
}

void Hand::displayHand() {
    for(Card card : cards){
        std::cout<< card.toString() << std::endl;
    }

}


