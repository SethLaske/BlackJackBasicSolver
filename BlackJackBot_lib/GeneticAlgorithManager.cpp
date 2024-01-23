//
// Created by small on 1/22/2024.
//

#include "GeneticAlgorithManager.h"

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
