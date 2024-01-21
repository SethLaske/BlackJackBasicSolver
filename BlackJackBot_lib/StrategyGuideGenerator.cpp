//
// Created by small on 1/21/2024.
//


#include "StrategyGuideGenerator.h"

const std::string StrategyGuideGenerator::COLUMNS[] = {"Player Hands", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Ace"};
const std::string StrategyGuideGenerator::ROWS[] = {"20", "19", "18", "17", "16", "15", "14", "13", "12", "11", "10", "9", "8", "7", "6", "5", "A11", "A10", "A9", "A8", "A7", "A6", "A5", "A4", "A3", "A2", "A1", "S11", "S10", "S9", "S8", "S7", "S6", "S5", "S4", "S3", "S2", "S1"};

const std::string StrategyGuideGenerator::NORMALOPTIONS[] = {"Stay", "Hit", "Double"};
const std::string StrategyGuideGenerator::SPLITOPTIONS[] = {"Stay", "Hit", "Double", "Split"};  //More specifics might be added later like Split/Stay or Split if can double

StrategyGuideGenerator::StrategyGuideGenerator() {
    srand(time(NULL));
    lenColumns = sizeof(COLUMNS)/sizeof(COLUMNS[0]);
    lenRows = sizeof(ROWS)/sizeof(ROWS[0]);
    lenNormalOptions = sizeof(NORMALOPTIONS)/sizeof(NORMALOPTIONS[0]);
    lenSplitOptions = sizeof(SPLITOPTIONS)/sizeof(SPLITOPTIONS[0]);
}

StrategyGuideGenerator::~StrategyGuideGenerator() {

}

std::string StrategyGuideGenerator::getRandomOption(const std::string &rowHead) {

    if(rowHead.empty()){
        std::cerr << "Empty string passed in" << std::endl;
        return "Stay";
    }
    char firstChar = rowHead.at(0);

    if(firstChar == 'S'){   //Splits have more options that can be used
        int index = rand() % lenSplitOptions;
        return SPLITOPTIONS[index];
    }

    int index = rand() % lenNormalOptions;
    return NORMALOPTIONS[index];
}

void StrategyGuideGenerator::createRandomGuide(const std::string &filePath) {
    if(!StrategyGuideHandler::isCSVFile(filePath)){
        return;
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open/create file '" << filePath << "'" <<  std::endl;
        return;
    }

    file << COLUMNS[0];
    for (int j = 1; j < lenColumns; j++) {
        std::cout << COLUMNS[j] << std::endl;
        file << "," << COLUMNS[j];
    }

    file << std::endl;
    for (int i = 0; i < lenRows; i++) {
        file << ROWS[i];

        for (int j = 1; j < lenColumns; j++) {
            file << "," << getRandomOption(ROWS[i]);
        }

        file << std::endl;
    }

    file.close();
}


