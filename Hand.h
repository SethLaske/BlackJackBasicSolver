//
// Created by small on 1/16/2024.
//

#ifndef HAND_H
#define HAND_H


#include <vector>
#include "Card.h"

class Hand {

public:
    Hand();
    ~Hand();

    virtual void addCard(const Card& newCard);
    virtual bool isBlackJack();

    //Returns the visible hand count
    int getHandValue() const;
    //Returns 1 if there is a softace
    int getSoftAceCount() const;

    //Prints out the hand
    virtual void displayHand();

protected:
    std::vector<Card> cards;

    int valueCount;
    int softAceCount;
};


#endif //HAND_H
