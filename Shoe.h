#ifndef SHOE_H
#define SHOE_H

#include "Card.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

class Shoe {
public:
    // Constructor with default value for the number of decks
    Shoe(int numberOfDecks, float minPenetration, float maxPenetration);

    //Shuffle the shoe, resulting in a full shoe
    void doShuffle();

    //Check if the shoe needs shuffling before shuffling
    bool tryShuffle();

    //Draw card from shoe
    Card drawCard();

    int getNumberOfDecks() const;



private:
    //Fill the deck
    void initShoe();

    void placeCutCard();

    // Private lists of cards
    std::vector<Card> availableCards;
    std::vector<Card> discardedCards;

    // Private variables
    int numberOfDecks;
    int currentCutCardIndex;
    float minPenetration;
    float maxPenetration;

    bool needToShuffle;
};

#endif // SHOE_H
