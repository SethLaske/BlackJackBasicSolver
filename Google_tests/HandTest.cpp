#include "lib\googletest\include\gtest/gtest.h"
#include "PlayerHand.h"

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

    EXPECT_EQ(fakeHand.isHandFinished(), true);
}
