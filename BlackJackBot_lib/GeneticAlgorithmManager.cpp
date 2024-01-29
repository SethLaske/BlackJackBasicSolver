//
// Created by small on 1/22/2024.
//

#include <algorithm>
#include "GeneticAlgorithmManager.h"
#include "StrategyGuideHandler.h"
#include "PlayerBot.h"
#include "Table.h"


GeneticAlgorithmManager::GeneticAlgorithmManager() {

    numberOfChildrenPerGeneration = 4;
    numberOfGenerations = 4;

    srand(time(nullptr));
}

GeneticAlgorithmManager::~GeneticAlgorithmManager() {

}

float GeneticAlgorithmManager::runGeneticAlgorithm(const std::string &rootFolderName, int testsPerChild, int childrenPerGeneration, int generationCount) {

    highestResult = -999;
    highestResultPath = "";

    if(!createFolder(rootFolderName)){
        std::cerr<< "Not running GA, because Root Folder '" << rootFolderName << "' can not be created"<<std::endl;
        return highestResult;
    }

    this->numberOfChildrenPerGeneration = childrenPerGeneration;
    this->numberOfGenerations = generationCount;

    spawnInitialGeneration(rootFolderName + "\\Gen0");

    std::string parentGenerationPath = rootFolderName + "\\Gen0";
    std::string nextGenerationPath = rootFolderName + "\\Gen1";

    for(int i = 0; i < numberOfGenerations; i ++){

        //std::cout << "Testing generation: " << i << std::endl;

        if(HouseRules::DISPLAYGENETICALGORITHMPROGRESS) {
            if (numberOfGenerations > HouseRules::GENETICALGORITHMPROGRESSINCREMENTS && i % (numberOfGenerations / HouseRules::GENETICALGORITHMPROGRESSINCREMENTS) == 0) {
                std::cout << (i * 100/numberOfGenerations) << "% completed with this trial" << std::endl;
            }
        }

        testGenerationStrategies(parentGenerationPath, testsPerChild);

        std::unordered_map<std::string, float> previousGenerationResults = getGenerationResults(parentGenerationPath);

        saveGenerationResultsToFile(parentGenerationPath + "\\_Generation_Results.txt", previousGenerationResults);

        processGenerationResults(previousGenerationResults);

        breedGeneration(previousGenerationResults, nextGenerationPath);
        parentGenerationPath = nextGenerationPath;
        nextGenerationPath = rootFolderName + "\\Gen" + std::to_string(i+2);

    }

    testGenerationStrategies(parentGenerationPath, testsPerChild);
    std::unordered_map<std::string, float> lastGenerationResults = getGenerationResults(parentGenerationPath);
    saveGenerationResultsToFile(parentGenerationPath + "\\_Generation_Results.txt", lastGenerationResults);

    std::cout << std::endl << "*******GA Recap*******" << std::endl;
    std::cout << "Highest Results: "<< highestResult << std::endl;
    std::cout << "Available at: "<< highestResultPath << std::endl;
    std::cout << "**********************" << std::endl;

    return highestResult;
}

void GeneticAlgorithmManager::spawnInitialGeneration(const std::string& generationFolderPath) {
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
    if (!CreateDirectoryA(folderPath.c_str(), nullptr)) {
        std::cerr << "Error: Unable to create directory " << folderPath << std::endl;
        return false;
    } else {
        return true;
    }
}

void GeneticAlgorithmManager::testGenerationStrategies(const std::string& generationFolderPath, int gamesPerStrategy) {

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
                std::string strategyFilePath = generationFolderPath + "\\" + findFileData.cFileName + strategyFileName;

                if (GetFileAttributes(strategyFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {

                    newStrategy.loadStrategyGuide(strategyFilePath);

                    table.runGameTesting(gamesPerStrategy);
                } else {
                    std::cerr << "Error: Strategy file not found in " << findFileData.cFileName << std::endl;
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

std::string GeneticAlgorithmManager::selectWeightedEntry(const std::unordered_map<std::string, float>& weightedMap) {
    float totalSum = 0.0f;
    for (const auto& entry : weightedMap) {
        totalSum += entry.second;
    }

    float randomNumber = rand() % (int)totalSum;

    float cumulativeSum = 0.0f;
    for (const auto& entry : weightedMap) {
        cumulativeSum += entry.second;
        if (randomNumber <= cumulativeSum) {
            return entry.first;
        }
    }

    if (!weightedMap.empty()) {
        return weightedMap.begin()->first;
    }

    return "";

}

std::unordered_map<std::string, float> GeneticAlgorithmManager::getGenerationResults(const std::string &generationFolderPath) {
    std::unordered_map<std::string, float> generationResults;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((generationFolderPath + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open directory " << generationFolderPath << " for testing." << std::endl;
        return generationResults;
    }


    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                std::string childFolderPath = generationFolderPath + "\\" + findFileData.cFileName;
                std::string resultsFilePath = childFolderPath + "\\Results.txt";

                // Check if Results.txt file exists in the current child folder
                if (GetFileAttributes(resultsFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {
                    // Open the Results.txt file and extract the float value
                    std::ifstream resultsFile(resultsFilePath);
                    if (resultsFile.is_open()) {
                        float resultValue;
                        resultsFile >> resultValue;
                        resultsFile.close();

                        // Add entry to parentResults map
                        generationResults[childFolderPath] = resultValue;
                    } else {
                        std::cerr << "Error: Unable to open Results.txt in " << childFolderPath << std::endl;
                    }
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    return generationResults;
}

void GeneticAlgorithmManager::saveGenerationResultsToFile(const std::string &filePath, std::unordered_map<std::string, float> results) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open/create file '" << filePath << " while saving" << std::endl;
        return;
    }

    file.clear();
    file.seekp(0, std::ios::beg);


    for(const auto& entry : results){
        file << entry.first << " scored: " << entry.second << "\n";
        if(entry.second > highestResult){
            highestResult = entry.second;
            highestResultPath = entry.first;
        }
    }

    file.close();

}

void GeneticAlgorithmManager::processGenerationResults(std::unordered_map<std::string, float> &results) {
    float lowestResult = 0;

    for(const auto& pair : results){
        if(pair.second < lowestResult){
            lowestResult = pair.second;
        }
        if(pair.second > 0){

            std::cerr << "********POSITIVE RESULTS********" << std::endl;
        }
    }

    for(const auto& pair : results){
        //I would like to find a way to scale out the data even more, so the highest results are even more heavily favored
        //results[pair.first] = pair.second - lowestResult + 1;
        results[pair.first] = pair.second - (lowestResult) + 1;
    }

    /*float percentToRemove = .5;
    std::vector<std::pair<std::string, float>> sortedMap(results.begin(), results.end());
    std::sort(sortedMap.begin(), sortedMap.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Step 2: Calculate the threshold value
    int thresholdIndex = static_cast<int>(sortedMap.size() * percentToRemove);

    // Step 3: Remove elements below the threshold
    for (int i = 0; i < thresholdIndex; ++i) {
        results.erase(sortedMap[i].first);
    }*/

}

void GeneticAlgorithmManager::breedGeneration(const std::unordered_map<std::string, float> &parentGenerationResults, const std::string &childGenerationFolderPath) {
    if(!createFolder(childGenerationFolderPath)){
        return;
    }

    /*int r = 1;
    for(const auto& pair : parentGenerationResults){
        if(createFolder(childGenerationFolderPath + childFolderName + "Repeat" + std::to_string(r))) {
            strategyGuideGenerator.mergeTwoGuides(pair.first + strategyFileName, pair.first + strategyFileName,
                                                  childGenerationFolderPath + childFolderName + "Repeat" +
                                                  std::to_string(r) + strategyFileName, true);
            r++;
        }
    }*/

    for(int i = 0; i < numberOfChildrenPerGeneration; i++){
        if(createFolder(childGenerationFolderPath + childFolderName + std::to_string(i + 1))){
            strategyGuideGenerator.mergeTwoGuides(selectWeightedEntry(parentGenerationResults) + strategyFileName, selectWeightedEntry(parentGenerationResults) + strategyFileName,
                                                  childGenerationFolderPath + childFolderName + std::to_string(i + 1) + strategyFileName, true);
        }
    }
}
