//
// Created by small on 1/16/2024.
//

#ifndef DEALERHAND_H
#define DEALERHAND_H

#include <iostream>
#include "Hand.h"

class DealerHand : public Hand{
public:
    //Checks for natural blackjack including the hidden card
    bool isBlackJack() override;
    void addHiddenCard(const Card& newCard);
    //Shows the hidden card and adds it to the hand
    void revealHiddenCard();

    //Prints the hand, and shows that there is a hidden card
    void displayHand() override;
    void clearHand() override;

private:
    Card hiddenCard = Card(Card::SPADES, Card::ACE);
};


#endif //DEALERHAND_H
