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

    void addCard(const Card& addedCard) override;
    float getBetSize() const;
    void doubleDown(const Card& addedCard);
    Card splitCards();

    bool canBeSplit;
    bool canBeDoubled;

private:
    float betSize;
};


#endif //PLAYERHAND_H
