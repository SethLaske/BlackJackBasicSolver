#include "Card.h"

const std::string Card::SUIT_STRINGS[] = { "Spades", "Hearts", "Diamonds",  "Clubs" };
const std::string Card::VALUE_STRINGS[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

Card::Card(Suit suit, Value value) : suit(suit), value(value) {

}

Card::~Card() {

}

std::string Card::toString() const {
    std::string suitStr;
    std::string valueStr;

    suitStr = SUIT_STRINGS[suit];
    valueStr = VALUE_STRINGS[value-1];


    return valueStr + " of " + suitStr;
}

int Card::getCardValue() const{
    if(value == ACE){
        return 11;
    } else if(value < TEN){
        return value;
    } else{
        return 10;
    }
}


