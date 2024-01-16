#include <iostream>
#include <string>
#include "StrategyGuideHandler.h"

using namespace std;

int main() {

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


    return 0;
}

