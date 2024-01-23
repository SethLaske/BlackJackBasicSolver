#ifndef GENETICALGORITHMANAGER_H
#define GENETICALGORITHMANAGER_H

#include "StrategyGuideGenerator.h"

class GeneticAlgorithManager {
public:
    GeneticAlgorithManager();
    ~GeneticAlgorithManager();

    //runGeneticAlgorithm(folder, children, waves)
private:
    int currentGeneration;

    int numberOfChildrenPerGeneration;
    int numberOfGenerations;
    //spawnInitialWave(folder)
    //testAllStrategies(folder)
    //breedWave(parentFolder, childFolder)
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
