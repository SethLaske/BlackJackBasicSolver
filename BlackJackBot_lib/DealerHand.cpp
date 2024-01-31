

#include "DealerHand.h"

bool DealerHand::isBlackJack() {
    if(cards.size() == 1 && (hiddenCard.getCardValue() + cards[0].getCardValue() == 21)){
        return true;
    }

    return false;
}

void DealerHand::addHiddenCard(const Card& newCard) {
    hiddenCard = newCard;
}

void DealerHand::revealHiddenCard() {
    addCard(hiddenCard);
}

void DealerHand::clearHand() {
    Hand::clearHand();
    /*cards.clear();
    valueCount = 0;
    softAceCount = 0;*/

}

void DealerHand::displayHand() {
    std::cout << "Dealer:" << std::endl;
    Hand::displayHand();
    if(cards.size() == 1){
        std::cout << "? of ?" << std::endl;
    }
}
