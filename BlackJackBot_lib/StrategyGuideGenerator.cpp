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

void StrategyGuideGenerator::createRandomGuideFile(const std::string &filePath) {
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
        //std::cout << COLUMNS[j] << std::endl;
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

void StrategyGuideGenerator::saveStrategyToFile(const std::string& filePath, std::unordered_map<std::string, std::array<std::string, 10>> strategy) {

    if(!StrategyGuideHandler::isCSVFile(filePath)){
        return;
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open/create file '" << filePath << "'" <<  std::endl;
        return;
    }

    // Iterate through the stored strategy and save to the file
    for (const auto& pair : strategy) {
        file << pair.first;

        for (const auto& entry : pair.second) {
            file << "," << entry;
        }

        file << std::endl;
    }

    file.close();
}

void StrategyGuideGenerator::mergeTwoGuides(const std::string &parentFilePath1, const std::string &parentFilePath2,
                                            const std::string &childFilePath) {
    std::unordered_map<std::string, std::array<std::string, (sizeof(COLUMNS)/sizeof(COLUMNS[0]))-1>> parentStrategy1 = makeStrategyFromFile(parentFilePath1);
    std::unordered_map<std::string, std::array<std::string, (sizeof(COLUMNS)/sizeof(COLUMNS[0]))-1>> parentStrategy2 = makeStrategyFromFile(parentFilePath2);
    std::unordered_map<std::string, std::array<std::string, (sizeof(COLUMNS)/sizeof(COLUMNS[0]))-1>> childStrategy;
    if(parentStrategy1.size() != lenRows + 1){
        std::cerr << "The first file does not have the proper number of rows";
        return;
    }

    if(parentStrategy2.size() != lenRows + 1){
        std::cerr << "The second file does not have the proper number of rows";
        return;
    }

    for (const auto& pair : parentStrategy1) {
        auto it = parentStrategy2.find(pair.first);
        if (it != parentStrategy2.end()) {
            int parent = rand() % 2;
            std::cout << "For the column with header " << pair.first << " the array will come from parent " << parent + 1 << std::endl;
            if(parent == 0){
                childStrategy[pair.first] = pair.second;
            } else{
                childStrategy[pair.first] = it->second;
            }
        } else {
            // Key not found, handle the error or add a new entry if needed
            std::cerr << "The second parent is missing a line" <<  std::endl;
        }

    }

    saveStrategyToFile(childFilePath, childStrategy);

}

std::unordered_map<std::string, std::array<std::string, 10>> StrategyGuideGenerator::makeStrategyFromFile(const std::string& filePath) {

    int possibleDealerCards = lenColumns - 1;   //The first entry is reserved for a header
    std::unordered_map<std::string, std::array<std::string, (sizeof(COLUMNS)/sizeof(COLUMNS[0]))-1>> strategy;

    if(!StrategyGuideHandler::isCSVFile(filePath)){
        return strategy;
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << filePath << "'" << std::endl;
        return strategy;
    }

    // Read and populate the  unordered_map
    std::string line;
    while (getline(file, line)) {

        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> values;

        while (getline(ss,token,',')) {
            values.push_back(token);
        }

        // Check for entries per line not correct
        if (values.size() < lenColumns) {
            std::cerr << "Error: Entries per line not met. Adding 'Overflow' for missing entries." << std::endl;
            values.resize(lenColumns, "Overflow");
        }else if (values.size() > lenColumns) {
            std::cerr << "Error: Entries per line exceeded. Cutting off additional entries." << std::endl;
            values.resize(lenColumns, "Overflow");
        }

        std::string key = values[0];

        std::array<std::string, (sizeof(COLUMNS)/sizeof(COLUMNS[0])-1)> strategyArray;
        for (int i = 0; i < possibleDealerCards; i++) {
            strategyArray[i] = values[i+1];
        }

        strategy[key] = strategyArray;
    }
    file.close();

    return strategy;
}
