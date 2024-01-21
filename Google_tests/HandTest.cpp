#include "lib\googletest\include\gtest/gtest.h"
#include "PlayerHand.h"
#include "DealerHand.h"

TEST(HandTestSuite, RegularHandBust){
    PlayerHand fakeHand(10);

    fakeHand.addCard({Card::SPADES, Card::SEVEN});
    fakeHand.addCard({Card::SPADES, Card::NINE});

    EXPECT_EQ(fakeHand.getHandValue(), 16);
    EXPECT_EQ(fakeHand.getSoftAceCount(), 0);
    EXPECT_EQ(fakeHand.isBlackJack(), false);
    EXPECT_EQ(fakeHand.canSplit(), false);
    EXPECT_EQ(fakeHand.canDouble(), true);
    EXPECT_EQ(fakeHand.isHandFinished(), false);

    fakeHand.addCard({Card::SPADES, Card::TEN});

    EXPECT_EQ(fakeHand.canDouble(), false);
    EXPECT_EQ(fakeHand.isHandFinished(), true);
}

TEST(HandTestSuite, DealerBlackjack){
    DealerHand dealerBlackJack;
    DealerHand dealerNoBlackJack;

    dealerNoBlackJack.addCard({Card::SPADES, Card::SEVEN});
    dealerNoBlackJack.addHiddenCard({Card::SPADES, Card::NINE});

    dealerBlackJack.addCard({Card::SPADES, Card::ACE});
    dealerBlackJack.addHiddenCard({Card::SPADES, Card::JACK});

    EXPECT_EQ(dealerNoBlackJack.isBlackJack(), false);
    EXPECT_EQ(dealerBlackJack.isBlackJack(), true);

    EXPECT_EQ(dealerNoBlackJack.getHandValue(), 7);

    dealerNoBlackJack.revealHiddenCard();
    EXPECT_EQ(dealerNoBlackJack.getHandValue(), 16);

    dealerNoBlackJack.addCard({Card::SPADES, Card::FIVE});

    EXPECT_EQ(dealerNoBlackJack.isBlackJack(), false);
    EXPECT_EQ(dealerNoBlackJack.getHandValue(), 21);
}

TEST(HandTestSuite, PlayerDoubling){

    PlayerHand fakeHand(10);

    fakeHand.addCard({Card::SPADES, Card::SIX});
    fakeHand.addCard({Card::SPADES, Card::FOUR});

    EXPECT_EQ(fakeHand.getHandValue(), 10);
    EXPECT_EQ(fakeHand.getSoftAceCount(), 0);
    EXPECT_EQ(fakeHand.isBlackJack(), false);
    EXPECT_EQ(fakeHand.canDouble(), true);
    EXPECT_EQ(fakeHand.isHandFinished(), false);

    fakeHand.addCard({Card::SPADES, Card::ACE});

    EXPECT_EQ(fakeHand.getHandValue(), 21);
    EXPECT_EQ(fakeHand.getSoftAceCount(), 1);
    EXPECT_EQ(fakeHand.isBlackJack(), false);
    EXPECT_EQ(fakeHand.canDouble(), false);
    EXPECT_EQ(fakeHand.isHandFinished(), true);    //Subject to change, you could hit a soft 21, but there is almost no reason to do so
}
