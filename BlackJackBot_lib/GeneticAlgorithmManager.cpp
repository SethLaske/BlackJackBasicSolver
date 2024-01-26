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

    srand(time(NULL));
}

GeneticAlgorithmManager::~GeneticAlgorithmManager() {

}


void GeneticAlgorithmManager::spawnInitialGeneration(const std::string& generationFolderPath) {
    //std::filesystem::path directoryPath = "path/to/your/directory";
    if(!createFolder(generationFolderPath)){
        return;
    }

    for(int i = 0; i < numberOfChildrenPerGeneration; i++){

        if(createFolder(generationFolderPath + childFolderName + std::to_string(i + 1))){
            strategyGuideGenerator.createRandomGuideFile(generationFolderPath + childFolderName + std::to_string(i + 1) + strategyFileName);
        }else{
            std::cerr << "While spawning the initial wave, was unable to spawn " + generationFolderPath + childFolderName + std::to_string(i + 1) << std::endl;
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

void GeneticAlgorithmManager::testGenerationStrategies(const std::string& generationFolderPath) {


    StrategyGuideHandler newStrategy;

    float bankRoll = 5000;
    PlayerBot playerBot(bankRoll, newStrategy);

    Table table(playerBot);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((generationFolderPath + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open directory " << generationFolderPath << " for testing." << std::endl;
        return;
    }

    do {

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                // Build the full path to the strategy file in the current subdirectory
                std::string strategyFilePath = generationFolderPath + "\\" + findFileData.cFileName + strategyFileName;

                // Check if the strategy file exists in the subdirectory
                if (GetFileAttributes(strategyFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {

                    //std::cout << "Passing in file " << strategyFilePath << " for testing" << std::endl;
                    newStrategy.loadStrategyGuide(strategyFilePath);

                    //Tests
                    table.runGameTesting(10);
                } else {
                    // Handle the case where the strategy file is not found in the subdirectory
                    std::cerr << "Error: Strategy file not found in " << findFileData.cFileName << std::endl;
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void GeneticAlgorithmManager::breedGeneration(const std::string& parentGenerationFolderName, const std::string& childGenerationFolderPath) {
    if(!createFolder(childGenerationFolderPath)){
        return;
    }


    std::unordered_map<std::string, float> parentResults;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((parentGenerationFolderName + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open directory " << parentGenerationFolderName << " for testing." << std::endl;
        return;
    }

    float lowestResult = 1;
    float highestResult = -1000;

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                std::string childFolderPath = parentGenerationFolderName + "\\" + findFileData.cFileName;
                std::string resultsFilePath = childFolderPath + "\\Results.txt";

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
                        parentResults[childFolderPath] = resultValue;
                    } else {
                        std::cerr << "Error: Unable to open Results.txt in " << childFolderPath << std::endl;
                    }
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    //TEMP: Saving the generation results here for now, just because they were already found here


    std::string filePath = parentGenerationFolderName + "\\Generation_Results.txt";

    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open/create file '" << filePath << " while saving" << std::endl;
        return;
    }

    file.clear();
    file.seekp(0, std::ios::beg);



    // Close the file


    for(const auto& entry : parentResults){

        std::cout << "Folder: " << entry.first << ", Results: " << entry.second;
        file << entry.first << " scored: " << entry.second << "\n";
        parentResults[entry.first] = entry.second - lowestResult + 1;
        std::cout << " Converts to: " << entry.second << std::endl;
    }

    file.close();

    //strategyGuideGenerator.mergeTwoGuides("file1", "file2", "child", true);
    for(int i = 0; i < numberOfChildrenPerGeneration; i++){
        if(createFolder(childGenerationFolderPath + childFolderName + std::to_string(i + 1))){
            std::cout << "Trying to breed files into: " << childGenerationFolderPath + childFolderName + std::to_string(i + 1) + strategyFileName << std::endl;
            strategyGuideGenerator.mergeTwoGuides(selectWeightedEntry(parentResults) + strategyFileName, selectWeightedEntry(parentResults) + strategyFileName,
                                                  childGenerationFolderPath + childFolderName + std::to_string(i + 1) + strategyFileName, true);
        }

    }


}

std::string GeneticAlgorithmManager::selectWeightedEntry(const std::unordered_map<std::string, float>& weightedMap) {
    // Calculate the total sum of probabilities
    float totalSum = 0.0f;
    for (const auto& entry : weightedMap) {
        totalSum += entry.second;
    }

    float randomNumber = rand() % (int)totalSum;

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