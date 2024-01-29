//
// Created by small on 1/16/2024.
//

#ifndef PLAYERHAND_H
#define PLAYERHAND_H

#include <memory>
#include "Hand.h"

class PlayerHand : public Hand{

public:
    PlayerHand(int betSize);
    ~PlayerHand();

    int getBetSize() const;
    int getHandSize() const;

    void stay();
    //Hit
    void addCard(const Card& addedCard) override;
    void doubleDown(const Card& addedCard);
    Card splitCards();

    bool canDouble() const;
    bool canSplit() const;
    bool isHandFinished() const;

    void displayHand() override;

private:
    bool handFinished;
    int betSize;
};


#endif //PLAYERHAND_H
