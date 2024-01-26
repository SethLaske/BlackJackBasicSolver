#ifndef GENETICALGORITHMANAGER_H
#define GENETICALGORITHMANAGER_H

#include "StrategyGuideGenerator.h"
#include <iostream>
#include <string>
#include <windows.h>

class GeneticAlgorithmManager {
public:
    GeneticAlgorithmManager();
    ~GeneticAlgorithmManager();

    //runGeneticAlgorithm(folder, children, waves)

    //Create the Gen 1 folder, the child folders, and completely randomized .csvs in each child
    void spawnInitialWave(const std::string& folderPath);
    void testAllStrategies(const std::string& folderPath);
    void breedWave(const std::string& parentFolderName, const std::string& childFolderPath);
private:
    StrategyGuideGenerator strategyGuideGenerator;
    int currentGeneration;

    int numberOfChildrenPerGeneration;
    int numberOfGenerations;

    bool createFolder(const std::string& folderPath);

    std::string selectWeightedEntry(const std::unordered_map<std::string, float>& weightedMap);
    //Run all .csvs in the gen folder at tables to get results

    //
    //breedWave(const std::string parentFolderPath, childFolderPath)
};

//Folder structure idea
/*
Folder
    Gen 1
        Strategy 1
            strategy.csv
            results.txt
        Strategy 2
            strategy.csv
            results.txt
        etc..
    Gen 2
    Gen 3
    etc...
    Best.csv
    Best.txt

*/
#endif //GENETICALGORITHMANAGER_H
