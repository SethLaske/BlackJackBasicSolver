#include "Shoe.h"

// Implementation for the constructor
Shoe::Shoe(int numberOfDecks, float minPenetration, float maxPenetration) {
    srand(time(NULL));

    this->numberOfDecks = numberOfDecks;
    this->minPenetration = minPenetration;
    this->maxPenetration = maxPenetration;

    initShoe();
}



// Implementation for the public function to shuffle the shoe
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

// Implementation for the public function to draw a card from the shoe
Card Shoe::drawCard() {

    if (!availableCards.empty()) {

        int index = rand() % availableCards.size();

        Card drawnCard = availableCards[index];

        availableCards.erase(availableCards.begin() + index);
        discardedCards.push_back(drawnCard);

        if(discardedCards.size() > currentCutCardIndex) {
            std::cout<< "WARNING CARDS LOW> Cards available: " << availableCards.size() << std::endl;
            //std::cout << "Dealing the: " << drawnCard.toString() << std::endl;
            needToShuffle = true;
        }

        //std::cout << "Dealing the: " << drawnCard.toString() << std::endl;
        return drawnCard;
    } else {
        //std::cout<< "ERROR: Cards available: " << availableCards.size() << " Cards discarded: " << discardedCards.size() << " Cut card index: " << currentCutCardIndex << std::endl;
        std::cerr << "Error: No available cards to draw." << std::endl;
        needToShuffle = true;
        return {Card::HEARTS, Card::TWO};
    }
}

bool Shoe::tryShuffle() {
    //std::cout<< "Cards available: " << availableCards.size() << " Cards discarded: " << discardedCards.size() << " Cut card index: " << currentCutCardIndex << std::endl;
    if(!needToShuffle){
        return false;
    }
    doShuffle();
    return true;
}

int Shoe::getNumberOfDecks() const {
    return numberOfDecks;
}

// Implementation for the private function to initialize the shoe
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
                //std::cout << "Adding card: " << newCard.toString() << " to the deck \n";
            }
        }
    }

    needToShuffle = false;
    placeCutCard();
}

void Shoe::placeCutCard() {

    int iterations = rand() + 1;
    float random = maxPenetration;
    for(int i = 0; i< iterations; i++){
        random = ((float) (rand() % 100)/100);
    }

    float diff = maxPenetration - minPenetration;
    float randomFloat = random * diff + minPenetration;

    currentCutCardIndex = (int)(randomFloat * (float)(numberOfDecks * 52));

    //std::cout << minPenetration << " - " << maxPenetration << " -> " << random << std::endl;
    std::cout << "The deck will need to be shuffled after: " << currentCutCardIndex << " cards." << std::endl;
}