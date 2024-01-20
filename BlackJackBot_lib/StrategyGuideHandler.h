#ifndef STRATEGYGUIDEHANDLER_H
#define STRATEGYGUIDEHANDLER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <array>

class StrategyGuideHandler {
public:
    StrategyGuideHandler(); // Constructor
    ~StrategyGuideHandler(); // Destructor

    void loadGuide(const std::string& csvFileName);
    void saveGuide(const std::string& csvFileName);
    std::basic_string<char> getEntry(const std::string& playerCards, int dealerCard);
    void editEntry(const std::string& playerCards, int dealerCard, std::string newMove);

private:
    static const int  POSSIBLE_DEALER_CARDS = 10;
    std::unordered_map<std::string, std::array<std::string,  POSSIBLE_DEALER_CARDS>> strategy;

    [[maybe_unused]] void printFile(const std::string& csvFileName);

    [[maybe_unused]] void printCurrentStrategy();

    bool isCSVFile(const std::string& fileName) const;
    bool isValidDealerNumber(int dealerCard) const;
};

#endif // STRATEGYGUIDEHANDLER_H
