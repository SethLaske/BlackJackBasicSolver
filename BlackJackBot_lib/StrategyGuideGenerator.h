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

    //This is being hardcoded until I find a workaround for the header
    std::unordered_map<std::string, std::array<std::string, 10>> makeStrategyFromFile(const std::string &filePath);
    void saveStrategyToFile(const std::string &filePath, std::unordered_map<std::string, std::array<std::string, 10>> strategy);
    void createRandomGuideFile(const std::string& filePath);
    void mergeTwoGuides(const std::string& parentFilePath1, const std::string& parentFilePath2, const std::string& childFilePath, bool mutate);

    static bool isCSVFile(const std::string &fileName);

private:
    std::string getRandomOption(const std::string& rowHead);
    std::array<std::string, 10> getRandomLine(const std::string &rowHead);


    const int lineMutationOdds = 10;    //Calculated as 1/x so if this is 20, its a 5% chance

    const static std::string COLUMNS[];
    int lenColumns;
    const static std::string ROWS[];
    int lenRows;

    const static std::string NORMALOPTIONS[];
    int lenNormalOptions;
    const static std::string SPLITOPTIONS[];
    int lenSplitOptions;


};


#endif //STRATEGYGUIDEGENERATOR_H
