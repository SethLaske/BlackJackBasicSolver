#include "lib\googletest\include\gtest/gtest.h"
#include "PlayerHand.h"
#include "DealerHand.h"

TEST(DealerHandTestSuite, DealerHiddenCard){
    DealerHand dealerHand;

    dealerHand.addCard({Card::SPADES, Card::SEVEN});
    dealerHand.addHiddenCard({Card::SPADES, Card::TEN});

    EXPECT_EQ(dealerHand.getHandValue(), 7);

    dealerHand.revealHiddenCard();

    EXPECT_EQ(dealerHand.getHandValue(), 17);
}

TEST(DealerHandTestSuite, DealerBlackJack){
    DealerHand dealerHand;

    dealerHand.addCard({Card::SPADES, Card::ACE});
    dealerHand.addHiddenCard({Card::SPADES, Card::TEN});

    EXPECT_EQ(dealerHand.getHandValue(), 11);
    EXPECT_EQ(dealerHand.isBlackJack(), true);

    dealerHand.revealHiddenCard();

    EXPECT_EQ(dealerHand.getHandValue(), 21);

    dealerHand.addCard({Card::SPADES, Card::QUEEN});

    EXPECT_EQ(dealerHand.getHandValue(), 21);
    EXPECT_EQ(dealerHand.isBlackJack(), false);
}