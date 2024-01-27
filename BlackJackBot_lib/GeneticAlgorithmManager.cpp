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

void GeneticAlgorithmManager::testGenerationStrategies(const std::string& generationFolderPath, const int gamesPerStrategy) {


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
                    table.runGameTesting(gamesPerStrategy);
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

    std::unordered_map<std::string, float> parentResults = getGenerationResults(parentGenerationFolderName);


    //TEMP: Saving the generation results here for now, just because they were already found here


    saveGenerationResultsToFile(parentGenerationFolderName + "\\Generation_Results.txt", parentResults);

    for(const auto& entry : parentResults){

        std::cout << "Folder: " << entry.first << ", Results: " << entry.second << std::endl;

    }

    processGenerationResults(parentResults);




    std::cout << "Processed files" << std::endl;


    for(const auto& entry : parentResults){

        std::cout << "Folder: " << entry.first << ", Results: " << entry.second << std::endl;

    }



    //strategyGuideGenerator.mergeTwoGuides("file1", "file2", "child", true);
    for(int i = 0; i < numberOfChildrenPerGeneration; i++){
        if(createFolder(childGenerationFolderPath + childFolderName + std::to_string(i + 1))){
            //std::cout << "Trying to breed files into: " << childGenerationFolderPath + childFolderName + std::to_string(i + 1) + strategyFileName << std::endl;
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
            //std::cout << "Randomly selected " << entry.first << " for breeding." << std::endl;
            return entry.first; // Return the selected entry
        }
    }

    if (!weightedMap.empty()) {
        return weightedMap.begin()->first;
    } else {
        return ""; // Return an empty string if the map is empty
    }
}

float GeneticAlgorithmManager::runGeneticAlgorithm(const std::string &rootFolderName, int childrenPerGeneration, int generationCount) {
    this->numberOfChildrenPerGeneration = childrenPerGeneration;
    this->numberOfGenerations = generationCount;
    currentGeneration = 0;
    int testsPerStrategy = 10000;
    spawnInitialGeneration(rootFolderName + "\\Gen0");

    /*for(int i = 0; i < numberOfGenerations; i ++){
        std::cout << "Testing generation: " << i << std::endl;
        testGenerationStrategies(rootFolderName + "\\Gen" + std::to_string(i), testsPerStrategy);
        std::cout << "Breeding generation: " << i << " into generation: " << (i+1) <<std::endl;
        breedGeneration(rootFolderName + "\\Gen" + std::to_string(i), rootFolderName + "\\Gen" + std::to_string(i+1));
    }
    testGenerationStrategies(rootFolderName + "\\Gen" + std::to_string(numberOfGenerations), testsPerStrategy);*/
    std::string parentGenerationPath = rootFolderName + "\\Gen0";
    std::string nextGenerationPath = rootFolderName + "\\Gen1";

    for(int i = 0; i < numberOfGenerations; i ++){
        std::cout << "Testing generation: " << i << std::endl;

        //std::cout << "Path: " << parentGenerationPath << std::endl;
        testGenerationStrategies(parentGenerationPath, testsPerStrategy);

        std::unordered_map<std::string, float> previousGenerationResults = getGenerationResults(parentGenerationPath);

        saveGenerationResultsToFile(parentGenerationPath + "\\Generation_Results.txt", previousGenerationResults);

        processGenerationResults(previousGenerationResults);

        std::cout << "Breeding generation: " << i << " into generation: " << (i+1) <<std::endl;
        breedGeneration(previousGenerationResults, nextGenerationPath);
        parentGenerationPath = nextGenerationPath;
        nextGenerationPath = rootFolderName + "\\Gen" + std::to_string(i+2);
        //std::cout << "I: " << i << "Parent Generation Path: " << parentGenerationPath << " Next Generation Path: " << nextGenerationPath << std::endl;
    }
    testGenerationStrategies(parentGenerationPath, testsPerStrategy);
    std::unordered_map<std::string, float> lastGenerationResults = getGenerationResults(parentGenerationPath);
    saveGenerationResultsToFile(parentGenerationPath + "\\Generation_Results.txt", lastGenerationResults);

    return 0;
}

std::unordered_map<std::string, float>
GeneticAlgorithmManager::getGenerationResults(const std::string &generationFolderPath) {
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

            std::cout << "********POSITIVE RESULTS********" << std::endl;
        }
    }

    for(const auto& pair : results){
        results[pair.first] = pair.second - lowestResult + 1;
    }

}

void GeneticAlgorithmManager::breedGeneration(const std::unordered_map<std::string, float> &parentGenerationResults,
                                              const std::string &childGenerationFolderPath) {
    if(!createFolder(childGenerationFolderPath)){
        return;
    }

    for(int i = 0; i < numberOfChildrenPerGeneration; i++){
        if(createFolder(childGenerationFolderPath + childFolderName + std::to_string(i + 1))){

            strategyGuideGenerator.mergeTwoGuides(selectWeightedEntry(parentGenerationResults) + strategyFileName, selectWeightedEntry(parentGenerationResults) + strategyFileName,
                                                  childGenerationFolderPath + childFolderName + std::to_string(i + 1) + strategyFileName, true);
        }

    }
}
