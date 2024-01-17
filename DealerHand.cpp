

#include "DealerHand.h"

bool DealerHand::isBlackJack() {
    if(cards.size() == 1 && (hiddenCard.getCardValue() + cards[0].getCardValue() == 21)){
        return true;
    }

    return false;
}

void DealerHand::dealHiddenCard(const Card& newCard) {
    hiddenCard = newCard;
}

void DealerHand::revealHiddenCard() {
    //std::cout << "The hidden card was the: " << hiddenCard.toString() << std::endl;
    addCard(hiddenCard);
}

void DealerHand::clearHand() {
    cards.clear();
    valueCount = 0;
    softAceCount = 0;

}

void DealerHand::displayHand() {
    std::cout << "Dealer:" << std::endl;
    Hand::displayHand();
    if(cards.size() == 1){
        std::cout << "? of ?" << std::endl;
    }

}
