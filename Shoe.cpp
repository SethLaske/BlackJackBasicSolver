#include "Shoe.h"

// Implementation for the constructor
Shoe::Shoe(int numberOfDecks, float minPenetration, float maxPenetration) {
    srand(time(NULL));

    this->numberOfDecks = numberOfDecks;
    this->minPenetration = minPenetration;
    this->maxPenetration = maxPenetration;

    //doShuffle();
    initShoe();
}



// Implementation for the public function to shuffle the shoe
void Shoe::doShuffle() {



    availableCards.insert(
            availableCards.end(),
            std::make_move_iterator(discardedCards.begin()),
            std::make_move_iterator(discardedCards.end())
    );

    // Clear the discarded cards vector
    discardedCards.clear();

    needToShuffle = false;
    placeCutCard();

}

// Implementation for the public function to draw a card from the shoe
Card Shoe::drawCard() {


    // Check if the availableCards vector is not empty
    if (!availableCards.empty()) {
        // Generate a random index within the availableCards vector
        int index = rand() % availableCards.size();

        // Get the randomly selected card
        Card drawnCard = availableCards[index];

        // Remove the drawn card from availableCards and add it to discardedCards
        availableCards.erase(availableCards.begin() + index);
        discardedCards.push_back(drawnCard);

        if(discardedCards.size() > currentCutCardIndex) {needToShuffle = true;}

        // Return the drawn card
        return drawnCard;
    } else {
        // Handle the case where there are no available cards
        std::cerr << "Error: No available cards to draw." << std::endl;
        needToShuffle = true;
        return {Card::HEARTS, Card::TWO}; // Placeholder, replace with appropriate logic

    }
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

    //srand (time(NULL));
    int iterations = rand() + 1;
    float random = maxPenetration;
    for(int i = 0; i< iterations; i++){
        random = ((float) (rand() % 100)/100);
    }

    float diff = maxPenetration - minPenetration;
    float randomFloat = random * diff + minPenetration;

    currentCutCardIndex = static_cast<int>(randomFloat * static_cast<float>(numberOfDecks * 52));

    std::cout << minPenetration << " - " << maxPenetration << " -> " << random << std::endl;

    std::cout << "The deck will need to be shuffled after: " << currentCutCardIndex << " cards." << std::endl;
}
