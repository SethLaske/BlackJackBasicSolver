#include <iostream>
#include <string>
#include "StrategyGuideHandler.h"
#include "Shoe.h"
#include "Card.h"
#include "PlayerHand.h"
#include "DealerHand.h"
#include "PlayerBot.h"
#include "Table.h"
#include "HouseRules.h"

//Test loading, editing, and saving a .csv into the strategyguidehandler
void testStrategyGuideHandler();
//Test drawing cards from a shoe and shuffling
void testShoe();
//Test giving the player bot a hand and getting a response
void testPlayerBot();
//Test running a table
void testTable();

using namespace std;

int main() {

    //testStrategyGuideHandler();
    //testShoe();
    //testPlayerBot();

    testTable();

    return 0;
}

void testStrategyGuideHandler() {
    StrategyGuideHandler newStrategy;

    newStrategy.loadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book1.csv)");

    cout << "The entry is: " << newStrategy.getEntry("PH", 11) << endl;

    newStrategy.editEntry("PH", 7, "Monkey");

    newStrategy.saveGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book2.csv)");

    /*StrategyGuideHandler* guideHandler = new StrategyGuideHandler();
    guideHandler->LoadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book1.csv)");
    guideHandler->GetEntry("10", 3);
    guideHandler->EditEntry("A7", 5, "X");
    guideHandler->SaveGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book2.csv)");
    delete guideHandler;*/
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

    newStrategy.loadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book1.csv)");

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
    newStrategy.loadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\ActualStrategy.csv)");
    float bankRoll = 5000;
    PlayerBot playerBot(bankRoll, newStrategy);

    Table table(playerBot);

    table.runGameTesting(400);
    //table.startGame();
}