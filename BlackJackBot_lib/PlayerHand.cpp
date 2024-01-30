//
// Created by small on 1/16/2024.
//

#include <iostream>
#include "PlayerHand.h"

PlayerHand::PlayerHand(int betSize) {
    this->betSize = betSize;
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
    if(handFinished){
        std::cerr << "The hand can not be hit" << std::endl;
    }
    Hand::addCard(addedCard);

    //If its equal to 21, then the player will be forced to stop, and if over then they busted and cant do anything
    if(valueCount >= 21){
        handFinished = true;
    }
}

void PlayerHand::doubleDown(const Card& addedCard) {
    if(!canDouble() || handFinished){
        std::cerr << "This hand can not be doubled" << std::endl;
        displayHand();
        return;
    }
    betSize *= 2;
    addCard(addedCard);
    handFinished = true;
}

Card PlayerHand::splitCards() {
    if(!canSplit() || handFinished){
        std::cerr << "This hand can't be split" << std::endl;
        displayHand();
        return {Card::SPADES, Card::ACE};
    }
    Card removedCard = cards.back();
    cards.pop_back();

    valueCount -= removedCard.getCardValue();
    //Handling aces, there will be a soft ace remaining
    if(removedCard.getCardValue() == 11){
        valueCount += 10;
    }

    return removedCard;
}

bool PlayerHand::canDouble() const{
    if(cards.size() != 2){
        return false;
    }
    //May need addition checks for doubling split aces, but for now ignoring
    return true;
}

bool PlayerHand::canSplit() const{
    if(cards.size() != 2){
        return false;
    }

    //This might also require some extra logic in checking the total number of times a hand can be split
    //Assumption is that splitting more than once will happen so infrequently that it won't affect the stats

    if(cards[0].getCardValue() == cards[1].getCardValue()){
        return true;
    }

    return false;
}

bool PlayerHand::isHandFinished() const {
    return handFinished;
}

int PlayerHand::getHandSize() const {
    return cards.size();
}

void PlayerHand::displayHand() {
    std::cout << "Player:" << std::endl;
    Hand::displayHand();
    std::cout << "Current value is "<< valueCount << " and the soft ace count is " << softAceCount << std::endl;
    std::cout << "For a bet of: " << betSize <<std::endl;
}




