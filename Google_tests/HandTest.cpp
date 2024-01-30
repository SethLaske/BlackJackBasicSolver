#include "lib\googletest\include\gtest/gtest.h"
#include "PlayerHand.h"
#include "DealerHand.h"

TEST(HandTestSuite, StandardHand){
    Hand hand;

    hand.addCard({Card::HEARTS, Card::FIVE});
    hand.addCard({Card::HEARTS, Card::ACE});

    EXPECT_EQ(hand.getHandValue(), 16);
    EXPECT_EQ(hand.getSoftAceCount(), 1);
    EXPECT_EQ(hand.isBlackJack(), false);

    hand.addCard({Card::HEARTS, Card::SEVEN});
    EXPECT_EQ(hand.getHandValue(), 13);
    EXPECT_EQ(hand.getSoftAceCount(), 0);
    EXPECT_EQ(hand.isBlackJack(), false);

    hand.addCard({Card::HEARTS, Card::EIGHT});
    EXPECT_EQ(hand.getHandValue(), 21);
    EXPECT_EQ(hand.getSoftAceCount(), 0);
    EXPECT_EQ(hand.isBlackJack(), false);
}

TEST(HandTestSuite, BlackjackHand){
    Hand hand;

    hand.addCard({Card::HEARTS, Card::QUEEN});
    hand.addCard({Card::HEARTS, Card::ACE});

    EXPECT_EQ(hand.getHandValue(), 21);
    EXPECT_EQ(hand.getSoftAceCount(), 1);
    EXPECT_EQ(hand.isBlackJack(), true);

    hand.addCard({Card::HEARTS, Card::ACE});
    EXPECT_EQ(hand.getHandValue(), 12);
    EXPECT_EQ(hand.getSoftAceCount(), 0);
    EXPECT_EQ(hand.isBlackJack(), false);

    hand.addCard({Card::HEARTS, Card::NINE});
    EXPECT_EQ(hand.getHandValue(), 21);
    EXPECT_EQ(hand.getSoftAceCount(), 0);
    EXPECT_EQ(hand.isBlackJack(), false);
}