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

#include "StrategyGuideHandler.h"

class StrategyGuideGenerator {
public:
    StrategyGuideGenerator();
    ~StrategyGuideGenerator();

    //This is being hardcoded until I find a workaround for the header
    std::unordered_map<std::string, std::array<std::string, 10>> makeStrategyFromFile(const std::string &filePath);
    void saveStrategyToFile(const std::string &filePath, std::unordered_map<std::string, std::array<std::string, 10>> strategy);
    void createRandomGuideFile(const std::string& filePath);
    void mergeTwoGuides(const std::string& parentFilePath1, const std::string& parentFilePath2, const std::string& childFilePath);

private:
    std::string getRandomOption(const std::string& rowHead);


    int lenColumns;
    const static std::string ROWS[];
    int lenRows;

    const static std::string NORMALOPTIONS[];
    int lenNormalOptions;
    const static std::string SPLITOPTIONS[];
    int lenSplitOptions;
    const static std::string COLUMNS[];



};


#endif //STRATEGYGUIDEGENERATOR_H
