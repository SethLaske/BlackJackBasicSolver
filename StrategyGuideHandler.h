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

    void LoadGuide(const std::string& fileName);
    void SaveGuide(const std::string& fileName);
    std::basic_string<char> GetEntry(const std::string& playerCards, int dealerCard);
    void EditEntry(const std::string& playerCards, int dealerCard, std::string newMove);

private:
    static const int possibleDealerCards = 10;
    std::unordered_map<std::string, std::array<std::string, possibleDealerCards>> strategy;

    void PrintFile(const std::string& fileName);
    void PrintCurrentStrategy();

    bool CheckForValidDealerNumber(int dealerCard);
    bool CheckForCSV(const std::string& fileName);
};

#endif // STRATEGYGUIDEHANDLER_H
