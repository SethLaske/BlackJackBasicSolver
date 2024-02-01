#ifndef STRATEGYGUIDEHANDLER_H
#define STRATEGYGUIDEHANDLER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <array>
#include "StrategyGuideGenerator.h"

class StrategyGuideHandler {
public:
    StrategyGuideHandler();
    ~StrategyGuideHandler();

    void loadStrategyGuide(const std::string& csvFileName);
    void saveStrategyGuide(const std::string& csvFileName);

    void saveResults(float results);

    std::basic_string<char> getEntry(const std::string& playerCards, int dealerCard);
    //void editEntry(const std::string& playerCards, int dealerCard, std::string newMove);

    static const int  POSSIBLE_DEALER_CARDS = 10;
private:
    std::string folderPath;


    std::unordered_map<std::string, std::array<std::string,  POSSIBLE_DEALER_CARDS>> strategy;

    [[maybe_unused]] void printFile(const std::string& csvFileName);

    [[maybe_unused]] void printCurrentStrategy();

    void setNewFolder(const std::string& folderPath);
    bool isValidDealerNumber(int dealerCard) const;
};

#endif // STRATEGYGUIDEHANDLER_H
