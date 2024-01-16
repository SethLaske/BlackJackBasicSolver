#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "StrategyGuideHandler.h"

using namespace std;

typedef struct{
    char responses[10];
} Responses;


/*

std::vector<std::vector<char>> loadCSV(const std::string& filename) {
    std::vector<std::vector<char>> data;

    // Get the current working directory
    std::filesystem::path currentPath = std::filesystem::current_path();

    // Construct the full path to the CSV file
    std::filesystem::path filePath = currentPath / filename;

    std::ifstream file(filePath.string());
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> row;
        std::istringstream ss(line);
        char value;
        while (ss >> value) {
            row.push_back(value);
            if (ss.peek() == ',') ss.ignore();
        }
        data.push_back(row);
    }

    if (file.bad()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        file.close();
        return data;
    }

    file.close();
    return data;
}

// Function to get a character from the data structure using headers
char getCharacter(const std::vector<std::vector<char>>& data, char stringHeader, int intHeader) {
    // Find the indices corresponding to the given headers
    int rowIndex = -1, colIndex = -1;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i][0] == stringHeader) {
            rowIndex = i;
            break;
        }
    }
    if (rowIndex == -1) {
        std::cerr << "String header not found: " << stringHeader << std::endl;
        return '\0'; // Return null character for error
    }

    for (size_t j = 0; j < data[0].size(); ++j) {
        if (static_cast<int>(data[0][j] - '0') == intHeader) {
            colIndex = j;
            break;
        }
    }
    if (colIndex == -1) {
        std::cerr << "Int header not found: " << intHeader << std::endl;
        return '\0'; // Return null character for error
    }

    // Return the character at the specified indices
    return data[rowIndex][colIndex];
}

// Function to set a character in the data structure using headers
void setCharacter(std::vector<std::vector<char>>& data, char stringHeader, int intHeader, char value) {
    // Find the indices corresponding to the given headers
    int rowIndex = -1, colIndex = -1;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i][0] == stringHeader) {
            rowIndex = i;
            break;
        }
    }
    if (rowIndex == -1) {
        std::cerr << "String header not found: " << stringHeader << std::endl;
        return; // Return for error
    }

    for (size_t j = 0; j < data[0].size(); ++j) {
        if (static_cast<int>(data[0][j] - '0') == intHeader) {
            colIndex = j;
            break;
        }
    }
    if (colIndex == -1) {
        std::cerr << "Int header not found: " << intHeader << std::endl;
        return; // Return for error
    }

    // Set the character at the specified indices
    data[rowIndex][colIndex] = value;
}

// Function to save data to CSV file
void saveCSV(const std::vector<std::vector<char>>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (const auto& value : row) {
            file << value << ",";
        }
        file.seekp(-1, std::ios_base::end); // Remove trailing comma
        file << "\n";
    }

    file.close();
}

void runGPT(){
    // Load data from CSV file
    std::vector<std::vector<char>> data = loadCSV("Book1.csv");

    // Example: Get character at A7 and int header 9
    char character = getCharacter(data, 'A', 7);
    std::cout << "Character at A7, 9: " << character << std::endl;

    // Example: Set character at A7 and int header 9 to 'X'
    setCharacter(data, 'A', 7, 'X');

    // Save modified data to a new CSV file
    saveCSV(data, "modified_file.csv");
}*/

/*void create()
{
    // file pointer
    std::fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("reportcard.csv", std::ios::out | std::ios::app);

    std::cout << "Enter the details of 5 students:"
         << " roll name maths phy chem bio"
    << std::endl;

    int i, roll, phy, chem, math, bio;
    std::string name;

    // Read the input
    for (i = 0; i < 5; i++) {

        std::cin >> roll
            >> name
            >> math
            >> phy
            >> chem
            >> bio;

        // Insert the data to file
        fout << roll << ", "
             << name << ", "
             << math << ", "
             << phy << ", "
             << chem << ", "
             << bio
             << "\n";
    }
}*/

/*
 * ifstream inputFile;
    inputFile.open("C:\\Users\\small\\CLionProjects\\BasicStrategySolver\Book1.csv");

    string line = "";

    while (getline(inputFile, line)){

        string playerHand;

        stringstream inputString(line);
        getline(inputString, playerHand, ',');
        line = "";
    }

    cout << "Hello World" << endl;*/
int main() {

    StrategyGuideHandler newStrategy;

    newStrategy.LoadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book1.csv)");

    cout << "The entry is: " << newStrategy.GetEntry("PH", 11) << endl;

    newStrategy.EditEntry("PH", 10, "Monkey");

    newStrategy.SaveGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book2.csv)");

    /*StrategyGuideHandler* guideHandler = new StrategyGuideHandler();

    guideHandler->LoadGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book1.csv)");

    guideHandler->GetEntry("10", 3);

    guideHandler->EditEntry("A7", 5, "X");

    guideHandler->SaveGuide(R"(C:\Users\small\CLionProjects\BasicStrategySolver\Book2.csv)");

    delete guideHandler;*/


    return 0;
}

