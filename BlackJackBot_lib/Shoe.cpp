#include "Shoe.h"

// Implementation for the constructor
Shoe::Shoe(int numberOfDecks, float minPenetration, float maxPenetration) {
    srand(time(NULL));

    this->numberOfDecks = numberOfDecks;
    this->minPenetration = minPenetration;
    this->maxPenetration = maxPenetration;

    initShoe();
}



void Shoe::doShuffle() {

    availableCards.insert(
            availableCards.end(),
            std::make_move_iterator(discardedCards.begin()),
            std::make_move_iterator(discardedCards.end())
    );

    discardedCards.clear();

    needToShuffle = false;
    placeCutCard();
}

Card Shoe::drawCard() {

    if (!availableCards.empty()) {

        int index = rand() % availableCards.size();

        Card drawnCard = availableCards[index];

        availableCards.erase(availableCards.begin() + index);
        discardedCards.push_back(drawnCard);

        if(discardedCards.size() > currentCutCardIndex) {
            needToShuffle = true;
        }

        return drawnCard;
    } else {
        std::cerr << "Error: No available cards to draw." << std::endl;
        needToShuffle = true;
        return {Card::HEARTS, Card::TWO};
    }
}

bool Shoe::tryShuffle() {
    if(!needToShuffle){
        return false;
    }
    doShuffle();
    return true;
}

int Shoe::getNumberOfDecks() const {
    return numberOfDecks;
}

void Shoe::initShoe() {
    availableCards.clear();
    discardedCards.clear();

    for (int s = Card::SPADES; s <= Card::CLUBS; s++ )
    {
        auto suit = static_cast<Card::Suit>(s);
        for (int v = Card::ACE; v <= Card::KING; v++ )
        {
            auto value = static_cast<Card::Value>(v);

            for(int i = 0; i < numberOfDecks; i ++){
                Card newCard = Card(suit, value);
                availableCards.push_back(newCard);
            }
        }
    }

    needToShuffle = false;
    placeCutCard();
}

void Shoe::placeCutCard() {

    //Getting a value 0-1, multiply it by the difference, and then add it to the minimum to get a value between the min and max
    int iterations = rand() + 1;
    float random = maxPenetration;
    for(int i = 0; i< iterations; i++){
        random = ((float) (rand() % 100)/100);
    }

    float diff = maxPenetration - minPenetration;
    float randomFloat = random * diff + minPenetration;

    currentCutCardIndex = (int)(randomFloat * (float)(numberOfDecks * 52));
}