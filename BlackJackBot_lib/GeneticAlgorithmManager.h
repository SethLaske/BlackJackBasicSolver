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
    void spawnInitialGeneration(const std::string& generationFolderPath);
    void testGenerationStrategies(const std::string& generationFolderPath);
    void breedGeneration(const std::string& parentGenerationFolderName, const std::string& childGenerationFolderPath);
private:
    StrategyGuideGenerator strategyGuideGenerator;
    int currentGeneration;

    int numberOfChildrenPerGeneration;
    int numberOfGenerations;

    const std::string strategyFileName = "\\Strategy.csv";
    const std::string childFolderName = "\\Child";

    bool createFolder(const std::string& folderPath);

    std::string selectWeightedEntry(const std::unordered_map<std::string, float>& weightedMap);
    //Run all .csvs in the gen folder at tables to get results

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
