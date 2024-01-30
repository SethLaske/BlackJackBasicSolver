#include "gtest/gtest.h"
#include "StrategyGuideHandler.h"

TEST(StrategyTestSuite, RegularLine){
    StrategyGuideHandler strategy;

    strategy.loadStrategyGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Google_tests\TestFile.csv)");

    EXPECT_EQ(strategy.getEntry("Test",2), "Two");
    EXPECT_EQ(strategy.getEntry("Test",11), "Ace");

    EXPECT_EQ(strategy.getEntry("Empty",5), "Overflow");
    EXPECT_EQ(strategy.getEntry("Overflow",11), "10");

    EXPECT_EQ(strategy.getEntry("Test",1), "Not Valid Dealer Card");
    EXPECT_EQ(strategy.getEntry("Test",12), "Not Valid Dealer Card");
}