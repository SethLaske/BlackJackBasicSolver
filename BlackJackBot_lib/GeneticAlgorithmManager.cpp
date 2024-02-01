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

        if(HouseRules::DISPLAYGENETICALGORITHMPROGRESS) {
            if (numberOfGenerations > HouseRules::GENETICALGORITHMPROGRESSINCREMENTS && i % (numberOfGenerations / HouseRules::GENETICALGORITHMPROGRESSINCREMENTS) == 0) {
                std::cout << (i * 100/numberOfGenerations) << "% completed with this trial" << std::endl;
            }
        }

        std::unordered_map<std::string, float> previousGenerationResults = testGeneration(parentGenerationPath, testsPerChild);

        saveGenerationResultsToFile(parentGenerationPath + "\\Generation_Results.txt", previousGenerationResults);

        //processGenerationResults(previousGenerationResults);

        breedGeneration(previousGenerationResults, nextGenerationPath);
        parentGenerationPath = nextGenerationPath;
        nextGenerationPath = rootFolderName + "\\Gen" + std::to_string(i+2);

    }

    std::unordered_map<std::string, float> lastGenerationResults = testGeneration(parentGenerationPath, testsPerChild);

    saveGenerationResultsToFile(parentGenerationPath + "\\Generation_Results.txt", lastGenerationResults);

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

        strategyGuideGenerator.createRandomGuideFile(generationFolderPath + "\\" + std::to_string(i + 1) + "_" + strategyFileName);

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

/*void GeneticAlgorithmManager::processGenerationResults(std::unordered_map<std::string, float> &results) {


    float percentToRemove = .5;
    std::vector<std::pair<std::string, float>> sortedMap(results.begin(), results.end());
    std::sort(sortedMap.begin(), sortedMap.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Step 2: Calculate the threshold value
    int thresholdIndex = static_cast<int>(sortedMap.size() * percentToRemove);

    // Step 3: Remove elements below the threshold
    for (int i = 0; i < thresholdIndex; ++i) {
        results.erase(sortedMap[i].first);
    }

}*/

void GeneticAlgorithmManager::breedGeneration(std::unordered_map<std::string, float> &parentGenerationResults, const std::string &childGenerationFolderPath) {
    if(!createFolder(childGenerationFolderPath)){
        return;
    }

    //PROCESSING
    float lowestResult = 0;

    for(const auto& pair : parentGenerationResults){
        if(pair.second < lowestResult){
            lowestResult = pair.second;
        }
        if(pair.second > 0){

            std::cerr << "********POSITIVE RESULTS********" << std::endl;
        }
    }

    for(const auto& pair : parentGenerationResults){
        //I would like to find a way to scale out the data even more, so the highest results are even more heavily favored
        parentGenerationResults[pair.first] = pair.second - (lowestResult) + 1;
    }

    float percentToRemove = .5;
    std::vector<std::pair<std::string, float>> sortedMap(parentGenerationResults.begin(), parentGenerationResults.end());
    std::sort(sortedMap.begin(), sortedMap.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Step 2: Calculate the threshold value
    int thresholdIndex = static_cast<int>(sortedMap.size() * percentToRemove);

    // Step 3: Remove elements below the threshold
    for (int i = 0; i < thresholdIndex; ++i) {
        parentGenerationResults.erase(sortedMap[i].first);
    }

    saveGenerationResultsToFile(childGenerationFolderPath + "\\Parent_Processed_Results.txt", parentGenerationResults);

    //BREEDING
    float percentToCopy = .2;
    int copiedFiles = static_cast<int>(sortedMap.size() * percentToCopy);
    float percentToMutate = .3;
    int mutatedFiles = static_cast<int>(sortedMap.size() * percentToMutate);

    int childCount = 0;


    for (int i = sortedMap.size() - 1; i >= sortedMap.size() - copiedFiles; --i) {
        std::cout << "Copying file " << sortedMap[i].first << " To: " << childGenerationFolderPath + "\\" + std::to_string(childCount+1) + "_" + strategyFileName << std::endl;
        strategyGuideGenerator.copyFile(sortedMap[i].first, childGenerationFolderPath + "\\" + std::to_string(childCount+1) + "_" + strategyFileName);
        childCount ++;
    }
    for (int i = sortedMap.size() - 1; i >= sortedMap.size() - mutatedFiles; --i) {
        std::cout << "Mutating file " << sortedMap[i].first << " with itself To: " << childGenerationFolderPath + "\\" + std::to_string(childCount+1) + "_" + strategyFileName << std::endl;
        strategyGuideGenerator.mergeTwoGuides(sortedMap[i].first, sortedMap[i].first, childGenerationFolderPath + "\\" + std::to_string(childCount+1) + "_" + strategyFileName, true);
        childCount ++;
    }

    while(childCount < numberOfChildrenPerGeneration){

        strategyGuideGenerator.mergeTwoGuides(selectWeightedEntry(parentGenerationResults), selectWeightedEntry(parentGenerationResults),
                                                  childGenerationFolderPath + "\\" + std::to_string(childCount + 1) + "_" + strategyFileName, true);
        childCount++;

    }
}

std::unordered_map<std::string, float> GeneticAlgorithmManager::testGeneration(const std::string &generationFolderPath, int gamesPerStrategy) {

    std::unordered_map<std::string, float> generationResults;
    StrategyGuideHandler strategyGuideHandler;

    float bankRoll = 5000;
    PlayerBot playerBot(bankRoll, strategyGuideHandler);

    Table table(playerBot);

    std::string searchPattern = generationFolderPath + "\\*" + strategyFileName;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPattern.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open directory " << generationFolderPath << " for testing." << std::endl;
        return generationResults;
    }

    float result = 0;
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::string strategyFilePath = generationFolderPath + "\\" + findFileData.cFileName;

            // MY CODE: Load strategy and run tests
            strategyGuideHandler.loadStrategyGuide(strategyFilePath);

            result = table.runGameTesting(gamesPerStrategy);
            generationResults[strategyFilePath] = result;

            if(result > highestResult){
                highestResult = result;
                highestResultPath = strategyFilePath;
            }
            //std::cout << "Adding entry: " << strategyFilePath << " : " << generationResults[strategyFilePath] << std::endl;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    return generationResults;
}
