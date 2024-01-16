#include <iostream>
#include <string>
#include "StrategyGuideHandler.h"
#include "Shoe.h"
#include "Card.h"

void testStrategyGuideHandler();
void testShoe();

using namespace std;

int main() {

    //testStrategyGuideHandler();
    testShoe();

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

    while (!shoe.needToShuffle) {
        //cout << shoe.drawCard().toString() << endl;
        shoe.drawCard();
    }

    shoe.doShuffle();

    while (!shoe.needToShuffle) {
        //cout << shoe.drawCard().toString() << endl;
        shoe.drawCard();
    }
}

