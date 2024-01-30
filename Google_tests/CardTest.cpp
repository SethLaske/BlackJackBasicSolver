#include "lib\googletest\include\gtest/gtest.h"
#include "Card.h"

TEST(CardTestSuite, CheckCardValue){
   Card aceCard(Card::SPADES, Card::ACE);
   EXPECT_EQ(aceCard.getCardValue(), 11);
    Card tenCard(Card::HEARTS, Card::TEN);
    EXPECT_EQ(tenCard.getCardValue(), 10);
    Card kingCard(Card::CLUBS, Card::KING);
    EXPECT_EQ(kingCard.getCardValue(), 10);
    Card twoCard(Card::HEARTS, Card::TWO);
    EXPECT_EQ(twoCard.getCardValue(), 2);
}

TEST(CardTestSuite, CheckCardString){
    Card sevenCard(Card::SPADES, Card::SEVEN);
    EXPECT_EQ(sevenCard.toString(), "Seven of Spades");
    Card queenCard(Card::HEARTS, Card::QUEEN);
    EXPECT_EQ(queenCard.toString(), "Queen of Hearts");
}
