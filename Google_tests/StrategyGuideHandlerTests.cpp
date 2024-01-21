#include "gtest/gtest.h"
#include "StrategyGuideHandler.h"

TEST(StrategyTestSuite, RegularLine){
    StrategyGuideHandler strategy;

    strategy.loadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Google_tests\TestFile.csv)");

    //EXPECT_EQ(strategy.getEntry("Test",2), "2");


}