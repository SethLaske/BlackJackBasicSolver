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
#include "StrategyGuideHandler.h"

class StrategyGuideGenerator {
public:
    StrategyGuideGenerator();
    ~StrategyGuideGenerator();

    void createRandomGuide(const std::string& filePath);
private:
    std::string getRandomOption(const std::string& rowHead);

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
