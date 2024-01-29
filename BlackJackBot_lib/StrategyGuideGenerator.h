//
// Created by small on 1/21/2024.
//

#ifndef STRATEGYGUIDEGENERATOR_H
#define STRATEGYGUIDEGENERATOR_H

#include <string>
#include <ctime>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>


class StrategyGuideGenerator {
public:
    StrategyGuideGenerator();
    ~StrategyGuideGenerator();

    //Each player hand is an entry with 10 possible responses based on the dealer's hand
    std::unordered_map<std::string, std::array<std::string, 10>> makeStrategyFromFile(const std::string &filePath);
    void saveStrategyToFile(const std::string &filePath, std::unordered_map<std::string, std::array<std::string, 10>> strategy);
    //Creates a random file, taking into consideration limited splits
    void createRandomGuideFile(const std::string& filePath);
    //Gets the data from two files and merges them into a single guide
    void mergeTwoGuides(const std::string& parentFilePath1, const std::string& parentFilePath2, const std::string& childFilePath, bool mutate);

    static bool isCSVFile(const std::string &fileName);

private:

    std::string getRandomOption(const std::string& rowHead);
    std::array<std::string, 10> getRandomLine(const std::string &rowHead);


    const int lineMutationOdds = 20;    //Calculated as 1/x so if this is 20, its a 5% chance

    //Represents every possible column, being the header and the different dealer hands
    const static std::string COLUMNS[];
    int lenColumns;
    //Includes every possible player hand, being hard values, splittable hands, and soft hands
    const static std::string ROWS[];
    int lenRows;

    //The options for a typical hand
    const static std::string NORMALOPTIONS[];
    int lenNormalOptions;
    //The options for a hand that can be split
    const static std::string SPLITOPTIONS[];
    int lenSplitOptions;


};


#endif //STRATEGYGUIDEGENERATOR_H
