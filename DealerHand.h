//
// Created by small on 1/16/2024.
//

#ifndef DEALERHAND_H
#define DEALERHAND_H

#include <iostream>
#include "Hand.h"

class DealerHand : public Hand{
public:
    bool isBlackJack() override;
    void dealHiddenCard(const Card& newCard);
    void revealHiddenCard();

    void displayHand() override;
    void clearHand();

private:
    Card hiddenCard = Card(Card::SPADES, Card::ACE);
};


#endif //DEALERHAND_H
