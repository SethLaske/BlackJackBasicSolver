#include "lib\googletest\include\gtest/gtest.h"
#include "PlayerHand.h"
#include "DealerHand.h"
#include "StrategyGuideHandler.h"
#include "PlayerBot.h"

TEST(PlayerBotSuite, Payments){
    StrategyGuideHandler strategy;
    strategy.loadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Google_tests\TestFile.csv)");

    PlayerBot player(500, strategy);

    player.getPaid(50);

    EXPECT_EQ(player.getMoney(), 550);
}

TEST(PlayerBotSuite, CheckQueriesHard){
    StrategyGuideHandler strategy;
    strategy.loadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Google_tests\TestFile.csv)");

    PlayerBot player(500, strategy);

    PlayerHand playerHand(10);

    playerHand.addCard({Card::SPADES, Card::SEVEN});
    playerHand.addCard({Card::SPADES, Card::NINE});

    DealerHand dealerHand;
    dealerHand.addCard({Card::SPADES, Card::NINE});
    dealerHand.addHiddenCard({Card::SPADES, Card::NINE});

    EXPECT_EQ(player.getPlayerAction(playerHand, dealerHand), PLAYERACTION::UNKNOWN);
}