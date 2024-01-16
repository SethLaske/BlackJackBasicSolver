//
// Created by small on 1/16/2024.
//

#include "Hand.h"

Hand::Hand() {

}

Hand::~Hand() {

}

void Hand::addCard(const Card& addedCard) {
    cards.push_back(addedCard);
    if(addedCard.getCardValue() == 11){
        softAceCount ++;
    }

    valueCount += addedCard.getCardValue();

    if(valueCount > 21 && softAceCount > 0){
        valueCount -= 10;
        softAceCount--;
    }
}

bool Hand::isBlackJack() {
    if(cards.size() != 2){
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


