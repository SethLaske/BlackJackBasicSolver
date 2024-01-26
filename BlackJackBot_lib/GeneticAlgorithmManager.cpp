//
// Created by small on 1/22/2024.
//

#include "GeneticAlgorithmManager.h"
#include "StrategyGuideHandler.h"
#include "PlayerBot.h"
#include "Table.h"

GeneticAlgorithmManager::GeneticAlgorithmManager() {
    currentGeneration = 0;

    //Default to these while testing other functions
    numberOfChildrenPerGeneration = 4;
    numberOfGenerations = 4;
}

GeneticAlgorithmManager::~GeneticAlgorithmManager() {

}


void GeneticAlgorithmManager::spawnInitialWave(const std::string& folderPath) {
    //std::filesystem::path directoryPath = "path/to/your/directory";
    if(!createFolder(folderPath)){
        return;
    }

    for(int i = 0; i < numberOfChildrenPerGeneration; i++){

        if(createFolder(folderPath + "\\Child" + std::to_string(i+1))){
            strategyGuideGenerator.createRandomGuideFile(folderPath + "\\Child" + std::to_string(i+1) + "\\Strategy.csv");
        }else{
            std::cerr << "While spawning the initial wave, was unable to spawn " + folderPath + "\\Child" + std::to_string(i+1)<< std::endl;
        }
    }


}

bool GeneticAlgorithmManager::createFolder(const std::string& folderPath) {

    if (!CreateDirectoryA(folderPath.c_str(), NULL)) {
        std::cerr << "Error: Unable to create directory " << folderPath << std::endl;
        return false;
    } else {
        //std::cout << "Directory " << folderPath << " created successfully." << std::endl;
        return true;
    }

}

void GeneticAlgorithmManager::testAllStrategies(const std::string& folderPath) {


    StrategyGuideHandler newStrategy;

    float bankRoll = 5000;
    PlayerBot playerBot(bankRoll, newStrategy);

    Table table(playerBot);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((folderPath + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open directory " << folderPath << " for testing." << std::endl;
        return;
    }

    do {

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                // Build the full path to the strategy file in the current subdirectory
                std::string strategyFilePath = folderPath + "\\" + findFileData.cFileName + "\\Strategy.csv";

                // Check if the strategy file exists in the subdirectory
                if (GetFileAttributes(strategyFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {

                    //std::cout << "Passing in file " << strategyFilePath << " for testing" << std::endl;
                    newStrategy.loadStrategyGuide(strategyFilePath);

                    //Tests
                    table.runGameTesting(1);
                } else {
                    // Handle the case where the strategy file is not found in the subdirectory
                    std::cerr << "Error: Strategy file not found in " << findFileData.cFileName << std::endl;
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void GeneticAlgorithmManager::breedWave(const std::string& parentFolderName, const std::string& childFolderPath) {
    if(!createFolder(childFolderPath)){
        return;
    }


    std::unordered_map<std::string, float> parentResults;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((parentFolderName + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open directory " << parentFolderName << " for testing." << std::endl;
        return;
    }

    float lowestResult = 1;
    float highestResult = -1000;

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                std::string childFolderPath1 = parentFolderName + "\\" + findFileData.cFileName;
                std::string resultsFilePath = childFolderPath1 + "\\Results.txt";

                // Check if Results.txt file exists in the current child folder
                if (GetFileAttributes(resultsFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {
                    // Open the Results.txt file and extract the float value
                    std::ifstream resultsFile(resultsFilePath);
                    if (resultsFile.is_open()) {
                        float resultValue;
                        resultsFile >> resultValue;
                        resultsFile.close();

                        if(resultValue > highestResult){
                            highestResult = resultValue;
                        }
                        if(resultValue < lowestResult){
                            lowestResult = resultValue;
                        }

                        // Add entry to parentResults map
                        parentResults[childFolderPath1] = resultValue;
                    } else {
                        std::cerr << "Error: Unable to open Results.txt in " << childFolderPath1 << std::endl;
                    }
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);


    for(const auto& entry : parentResults){

        std::cout << "Folder: " << entry.first << ", Results: " << entry.second << std::endl;
        parentResults[entry.first] = entry.second - lowestResult + 1;
    }


    //strategyGuideGenerator.mergeTwoGuides("file1", "file2", "child", true);
    for(int i = 0; i < numberOfChildrenPerGeneration; i++){
        if(createFolder(childFolderPath + "\\Child" + std::to_string(i+1))){
            std::cout << "Trying to breed files into: " << childFolderPath + "\\Child" + std::to_string(i+1) + "\\Strategy.csv" << std::endl;
            strategyGuideGenerator.mergeTwoGuides(selectWeightedEntry(parentResults) + "\\Strategy.csv", selectWeightedEntry(parentResults) + "\\Strategy.csv",
                                                  childFolderPath + "\\Child" + std::to_string(i+1) + "\\Strategy.csv", true);
        }

    }


}

std::string GeneticAlgorithmManager::selectWeightedEntry(const std::unordered_map<std::string, float>& weightedMap) {
    // Calculate the total sum of probabilities
    float totalSum = 0.0f;
    for (const auto& entry : weightedMap) {
        totalSum += entry.second;
    }

    // Generate a random number between 0 and the total sum
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, totalSum);
    float randomNumber = dis(gen);

    // Iterate through the map and find the entry whose cumulative probability range includes the random number
    float cumulativeSum = 0.0f;
    for (const auto& entry : weightedMap) {
        cumulativeSum += entry.second;
        if (randomNumber <= cumulativeSum) {
            std::cout << "Randomly selected " << entry.first << " for breeding." << std::endl;
            return entry.first; // Return the selected entry
        }
    }

    if (!weightedMap.empty()) {
        return weightedMap.begin()->first;
    } else {
        return ""; // Return an empty string if the map is empty
    }
}