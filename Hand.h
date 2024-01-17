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

    int getHandValue() const;
    int getSoftAceCount() const;

protected:

    std::vector<Card> cards;

    int valueCount;
    int softAceCount;

};


#endif //HAND_H
