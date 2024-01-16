//
// Created by small on 1/16/2024.
//

#ifndef BASICSTRATEGYSOLVER_PLAYERHAND_H
#define BASICSTRATEGYSOLVER_PLAYERHAND_H

#include <memory>
#include "Hand.h"

class PlayerHand : public Hand{

public:
    PlayerHand(int betSize);
    ~PlayerHand();

    void addCard(const Card& addedCard) override;
    int getBetSize() const;
    void doubleDown(const Card& addedCard);
    Card splitCards();

    bool canBeSplit;
    bool canBeDoubled;

private:
    int betSize;
};


#endif //BASICSTRATEGYSOLVER_PLAYERHAND_H
