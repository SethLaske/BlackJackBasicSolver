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
    explicit Shoe(int numberOfDecks = 3, float minPenetration = .4, float maxPenetration = .6);

    // Public function to shuffle the shoe
    void doShuffle();

    // Public function to draw a card from the shoe
    Card drawCard();

    int numberOfDecks;

    bool needToShuffle;

private:
    // Private function to initialize the shoe with a specified number of decks
    void initShoe();

    void placeCutCard();

    // Private lists of cards
    std::vector<Card> availableCards;
    std::vector<Card> discardedCards;

    // Private variables
    int currentCutCardIndex;
    float minPenetration;
    float maxPenetration;
};

#endif // SHOE_H
