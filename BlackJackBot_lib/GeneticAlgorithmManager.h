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

    //Run full genetic algorithm, and return the highest score
    float runGeneticAlgorithm(const std::string& rootFolderName, int testsPerChild, int childrenPerGeneration, int generationCount);
    //Create a randomized generation
    void spawnInitialGeneration(const std::string& generationFolderPath);
    //Test a generation (results for each file saved to Results.txt in corresponding folder)
    void testGenerationStrategies(const std::string& generationFolderPath, int gamesPerStrategy);
    //Creates a new folder and populates it based on the weighted (processed) scores in the parent Generation
    void breedGeneration(const std::unordered_map<std::string, float>& parentGenerationResults, const std::string& childGenerationFolderPath);
private:
    StrategyGuideGenerator strategyGuideGenerator;

    int numberOfChildrenPerGeneration;
    int numberOfGenerations;

    const std::string strategyFileName = "\\Strategy.csv";
    const std::string childFolderName = "\\Child";

    float highestResult;
    std::string highestResultPath;

    bool createFolder(const std::string& folderPath);

    //Scan through all subfolders for result.txt and return the map of strategy files with results
    std::unordered_map<std::string, float> getGenerationResults(const std::string& generationFolderPath);
    //Create a new file with the results
    void saveGenerationResultsToFile(const std::string& filePath, std::unordered_map<std::string, float> results);
    //Scale all results for weighted selections
    void processGenerationResults(std::unordered_map<std::string, float>& results);


    //Pick a random entry based on weighted results
    std::string selectWeightedEntry(const std::unordered_map<std::string, float>& weightedMap);
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


 Better idea

Root
    _Best.csv
    _Overview.txt (Contains the house rules, number of children, generations, and tests, and the best csv result and path)
    Gen 1
        _Generation_Results.txt
        C1_Strategy.csv
        C2_Strategy.csv
        ...
    Gen 1
        _Generation_Results.txt
        C1_Strategy.csv
        C2_Strategy.csv
        ...
*/
#endif //GENETICALGORITHMANAGER_H
