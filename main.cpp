#include <iostream>
#include <string>
#include "BlackJackBot_lib/StrategyGuideHandler.h"
#include "BlackJackBot_lib/Shoe.h"
#include "BlackJackBot_lib/Card.h"
#include "BlackJackBot_lib/PlayerHand.h"
#include "BlackJackBot_lib/DealerHand.h"
#include "BlackJackBot_lib/PlayerBot.h"
#include "BlackJackBot_lib/Table.h"
#include "BlackJackBot_lib/HouseRules.h"
#include "StrategyGuideGenerator.h"
#include "GeneticAlgorithmManager.h"
//#include <filesystem>

//Test loading, editing, and saving a .csv into the strategyguidehandler
void testStrategyGuideHandler();
//Test drawing cards from a shoe and shuffling
void testShoe();
//Test giving the player bot a hand and getting a response
void testPlayerBot();
//Test running a table
void testTable();
void testGuideGeneration();
void testGeneticAlgorithm();

using namespace std;

int main() {

    //testStrategyGuideHandler();
    //testShoe();
    //testPlayerBot();

    //testTable();
    //testGuideGeneration();
    testGeneticAlgorithm();

    return 0;
}

void testStrategyGuideHandler() {
    StrategyGuideHandler newStrategy;

    newStrategy.loadStrategyGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book1.csv)");

    cout << "The entry is: " << newStrategy.getEntry("PH", 11) << endl;

    //newStrategy.editEntry("PH", 7, "Monkey");

    newStrategy.saveStrategyGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book2.csv)");

}

void testShoe(){
    Shoe shoe(4, .5, .7);

    /*for (int i = 0; i < 5; ++i) {
        cout << shoe.drawCard().toString() << endl;
    }*/

    while (!shoe.tryShuffle()) {
        //cout << shoe.drawCard().toString() << endl;
        shoe.drawCard();
    }

    shoe.doShuffle();

    while (!shoe.tryShuffle()) {
        //cout << shoe.drawCard().toString() << endl;
        shoe.drawCard();
    }
}

void testPlayerBot(){
    StrategyGuideHandler newStrategy;

    newStrategy.loadStrategyGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book1.csv)");

    float bankRoll = 500;

    DealerHand dealerHand;
    PlayerHand playerHand(50);

    Shoe shoe(4, .5, .7);

    playerHand.addCard(shoe.drawCard());
    dealerHand.addHiddenCard(shoe.drawCard());
    playerHand.addCard(shoe.drawCard());
    dealerHand.addCard(shoe.drawCard());

    PlayerBot playerBot(bankRoll, newStrategy);

    playerBot.getPlayerAction(playerHand, dealerHand);
}

void testTable(){
    StrategyGuideHandler newStrategy;
    //newStrategy.loadGuide("ActualStrategy.csv");
    newStrategy.loadStrategyGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\ActualStrategy.csv)");
    float bankRoll = 5000;
    PlayerBot playerBot(bankRoll, newStrategy);

    Table table(playerBot);

    table.runGameTesting(100000);

    //StrategyGuideHandler newStrategy2(R"(C:\Users\small\CLionProjects\BasicStrategySolver\)");
    newStrategy.loadStrategyGuide("Book1.csv");

    //PlayerBot playerBot2(bankRoll, newStrategy2);

    //Table table2(playerBot2);

    table.runGameTesting(100000);
    //table.startGame();
}

void testGuideGeneration(){
    StrategyGuideGenerator strategyGuideGenerator;

    strategyGuideGenerator.createRandomGuideFile(R"(C:\Users\small\CLionProjects\BasicStrategySolver\RandomGuide1.csv)");
    strategyGuideGenerator.createRandomGuideFile(R"(C:\Users\small\CLionProjects\BasicStrategySolver\RandomGuide2.csv)");
    strategyGuideGenerator.mergeTwoGuides(R"(C:\Users\small\CLionProjects\BasicStrategySolver\RandomGuide1.csv)", R"(C:\Users\small\CLionProjects\BasicStrategySolver\RandomGuide2.csv)", R"(C:\Users\small\CLionProjects\BasicStrategySolver\RandomGuide3.csv)", true);

}

void testGeneticAlgorithm(){
    //cout << HouseRules::toString() << endl;

    GeneticAlgorithmManager geneticAlgorithmManager;

    geneticAlgorithmManager.runGeneticAlgorithm(R"(C:\Users\small\CLionProjects\BasicStrategySolver\GA_Testing\Root)", 500, 100, 100);
}