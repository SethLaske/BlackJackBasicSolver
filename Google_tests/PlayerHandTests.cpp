#include "lib\googletest\include\gtest/gtest.h"
#include "PlayerHand.h"

TEST(PlayerHandTestSuite, PlayerHandStay){
    PlayerHand playerHand(10);

    playerHand.addCard({Card::SPADES, Card::SEVEN});
    playerHand.addCard({Card::SPADES, Card::NINE});

    EXPECT_EQ(playerHand.getHandValue(), 16);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.canDouble(), true);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.addCard({Card::SPADES, Card::ACE});

    EXPECT_EQ(playerHand.getHandValue(), 17);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.stay();

    EXPECT_EQ(playerHand.getHandValue(), 17);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);
}

TEST(PlayerHandTestSuite, PlayerHandBust){
    PlayerHand playerHand(10);

    playerHand.addCard({Card::SPADES, Card::SIX});
    playerHand.addCard({Card::SPADES, Card::SIX});

    EXPECT_EQ(playerHand.getHandValue(), 12);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canSplit(), true);
    EXPECT_EQ(playerHand.canDouble(), true);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.addCard({Card::SPADES, Card::JACK});

    EXPECT_EQ(playerHand.getHandValue(), 22);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);
}

TEST(PlayerHandTestSuite, PlayerDoubling){

    PlayerHand playerHand(10);

    playerHand.addCard({Card::SPADES, Card::SIX});
    playerHand.addCard({Card::SPADES, Card::FOUR});

    EXPECT_EQ(playerHand.getHandValue(), 10);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), true);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.doubleDown({Card::SPADES, Card::ACE});

    EXPECT_EQ(playerHand.getBetSize(), 20);
    EXPECT_EQ(playerHand.getHandValue(), 21);
    EXPECT_EQ(playerHand.getSoftAceCount(), 1);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);    //Subject to change, you could hit a soft 21, but there is almost no reason to do so
}

TEST(PlayerHandTestSuite, PlayerSplitting){

    PlayerHand playerHand(10);

    playerHand.addCard({Card::SPADES, Card::EIGHT});
    playerHand.addCard({Card::SPADES, Card::EIGHT});

    EXPECT_EQ(playerHand.getHandValue(), 16);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), true);
    EXPECT_EQ(playerHand.canSplit(), true);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.splitCards();

    EXPECT_EQ(playerHand.getHandValue(), 8);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.addCard({Card::CLUBS, Card::EIGHT});

    EXPECT_EQ(playerHand.getHandValue(), 16);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), true);
    EXPECT_EQ(playerHand.canSplit(), true);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.addCard({Card::CLUBS, Card::EIGHT});

    EXPECT_EQ(playerHand.getHandValue(), 24);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);
}

TEST(PlayerHandTestSuite, FinishedHandValidation){
    PlayerHand playerHand(10);

    playerHand.addCard({Card::SPADES, Card::QUEEN});
    playerHand.addCard({Card::SPADES, Card::KING});

    EXPECT_EQ(playerHand.getHandValue(), 20);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), true);
    EXPECT_EQ(playerHand.canSplit(), true);
    EXPECT_EQ(playerHand.isHandFinished(), false);

    playerHand.stay();

    EXPECT_EQ(playerHand.getHandValue(), 20);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);

    playerHand.addCard({Card::SPADES, Card::ACE});

    EXPECT_EQ(playerHand.getHandValue(), 20);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);

    playerHand.doubleDown({Card::SPADES, Card::ACE});

    EXPECT_EQ(playerHand.getBetSize(), 10);
    EXPECT_EQ(playerHand.getHandValue(), 20);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);

    playerHand.splitCards();

    EXPECT_EQ(playerHand.getHandSize(), 2);
    EXPECT_EQ(playerHand.getHandValue(), 20);
    EXPECT_EQ(playerHand.getSoftAceCount(), 0);
    EXPECT_EQ(playerHand.isBlackJack(), false);
    EXPECT_EQ(playerHand.canDouble(), false);
    EXPECT_EQ(playerHand.canSplit(), false);
    EXPECT_EQ(playerHand.isHandFinished(), true);
}