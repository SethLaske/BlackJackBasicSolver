//
// Created by small on 1/22/2024.
//

#include "GeneticAlgorithManager.h"
#include "StrategyGuideHandler.h"

GeneticAlgorithManager::GeneticAlgorithManager() {
    currentGeneration = 0;

    //Default to these while testing other functions
    numberOfChildrenPerGeneration = 4;
    numberOfGenerations = 4;
}

GeneticAlgorithManager::~GeneticAlgorithManager() {

}


void GeneticAlgorithManager::spawnInitialWave(const std::string folderPath) {
    //std::filesystem::path directoryPath = "path/to/your/directory";
    if(!createFolder(folderPath)){
        return;
    }

    for(int i = 0; i < numberOfChildrenPerGeneration; i++){

        if(createFolder(folderPath + "\\Child" + std::to_string(i+1))){
            strategyGuideGenerator.createRandomGuideFile(folderPath + "\\Child" + std::to_string(i+1) + "\\strategy.csv");
        }

    }




}

bool GeneticAlgorithManager::createFolder(const std::string folderPath) {
    // Check if the directory already exists
    /*if (std::filesystem::exists(folderPath)) {
        return false;
    }

    return (std::filesystem::create_directory(folderPath));*/

    if (!CreateDirectoryA(folderPath.c_str(), NULL)) {
        std::cerr << "Error: Unable to create directory " << folderPath << std::endl;
        return false;
    } else {
        std::cout << "Directory " << folderPath << " created successfully." << std::endl;
        return true;
    }

    return false;
}

void GeneticAlgorithManager::testAllStrategies(const std::string folderName) {
    /*create a strategy guide handler StrategyGuideHandler newStrategy(foldername + "\\")");

    folderName leads to a director that has multiple sub directories

    check that strategy.csv is in each subdirectory and do the following lines of code
        newStrategy.loadStrategy(foldername + subcirectory name + "strategy.csv")
        //Ill insert code here

    */
    StrategyGuideHandler newStrategy(folderName + "\\");

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((folderName + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open directory " << folderName << std::endl;
        return;
    }

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                // Build the full path to the strategy file in the current subdirectory
                std::string strategyFilePath = folderName + "\\" + findFileData.cFileName + "\\strategy.csv";

                // Check if the strategy file exists in the subdirectory
                if (GetFileAttributes(strategyFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {
                    // Load the strategy from the CSV file

                    newStrategy.loadStrategyGuide(strategyFilePath);

                    //Tests
                } else {
                    // Handle the case where the strategy file is not found in the subdirectory
                    std::cerr << "Error: Strategy file not found in " << findFileData.cFileName << std::endl;
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
