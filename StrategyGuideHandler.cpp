

#include "StrategyGuideHandler.h"

using namespace std;

// Constructor
StrategyGuideHandler::StrategyGuideHandler() {
    strategy = std::unordered_map<std::string, std::array<std::string, 10>>();

    cout << "Created a strategy guide" << endl ;
}

// Destructor
StrategyGuideHandler::~StrategyGuideHandler() {
    // Clean up resources if needed
    cout << "Deleting the strategy guide" << endl ;
}

void StrategyGuideHandler::LoadGuide(const std::string& fileName) {

    if(CheckForCSV(fileName) == false){ return;}


    // Try to open the file
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << fileName << "'" << std::endl;
        return;
    }

    // Set the total number of entries per line
    const int entriesPerLine = possibleDealerCards + 1;

    // Read and populate the std::unordered_map
    std::string line;
    while (std::getline(file, line)) {
        // Tokenize the line based on commas
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> values;

        // Extract values from the line
        while (std::getline(ss, token, ',')) {
            values.push_back(token);
        }

        // Check for entries per line not correct
        if (values.size() < entriesPerLine) {
            std::cerr << "Error: Entries per line not met. Adding 'NULL' for missing entries." << std::endl;
            values.resize(entriesPerLine, "BJ");
        }else if (values.size() > entriesPerLine) {
            std::cerr << "Error: Entries per line exceeded. Cutting off additional entries." << std::endl;
            values.resize(entriesPerLine, "BJ");
        }

        std::string key = values[0];

        std::array<std::string, possibleDealerCards> strategyArray;
        for (int i = 0; i < possibleDealerCards; i++) {
            strategyArray[i] = values[i+1];
        }

        // Add the entry
        strategy[key] = strategyArray;
    }

    file.close();

    //PrintCurrentStrategy();
}

void StrategyGuideHandler::SaveGuide(const std::string& fileName) {

    if(CheckForCSV(fileName) == false){ return;}

    // Try to open the file for writing
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open/create file '" << fileName << "'" << std::endl;
        return;
    }

    // Iterate through the stored strategy and save to the file
    for (const auto& pair : strategy) {
        file << pair.first;

        // Save each entry in the array
        for (const auto& entry : pair.second) {
            file << "," << entry;
        }

        file << std::endl;
    }

    file.close();
}

basic_string<char> StrategyGuideHandler::GetEntry(const std::string& playerCards, int dealerCard) {

    //Dealer can have a 2-11, but the indexes will correspond to 0-9
    dealerCard -= 2;

    if(CheckForValidDealerNumber(dealerCard) == false){ return "F";}

    // Check if the key exists in the strategy map
    auto it = strategy.find(playerCards);
    if (it != strategy.end()) {
        // Key found, modify the corresponding entry
        std::array<std::string, possibleDealerCards>& arrayPtr = it->second;
        // Perform modification here, for example:
        return arrayPtr[dealerCard];
    } else {
        // Key not found, handle the error or add a new entry if needed
        std::cerr << "Entry not found for key: " << playerCards << std::endl;

    }

    return "L";
}

void StrategyGuideHandler::EditEntry(const std::string& playerCards, int dealerCard, string newMove) {

    //Dealer can have a 2-11, but the indexes will correspond to 0-9
    dealerCard -= 2;

    if(CheckForValidDealerNumber(dealerCard) == false){ return;}

    // Check if the key exists in the strategy map
    auto it = strategy.find(playerCards);
    if (it != strategy.end()) {
        // Key found, modify the corresponding entry
        std::array<std::string, possibleDealerCards>& arrayPtr = it->second;
        // Perform modification here, for example:
        arrayPtr[dealerCard] = newMove;
    } else {
        // Key not found, handle the error or add a new entry if needed
        std::cerr << "Entry not found for key: " << playerCards << std::endl;
        // Add new entry logic if required
        return;
    }

    //PrintCurrentStrategy();
}

void StrategyGuideHandler::PrintFile(const string &fileName) {
    cout << "Printing a file" << endl ;


    // Check if the file name has a .csv extension
    if (fileName.size() < 4 || fileName.substr(fileName.size() - 4) != ".csv") {
        std::cerr << "Error: Invalid file format. Please provide a .csv file." << std::endl;
        return;
    }

    // Try to open the file
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << fileName << "'" << std::endl;
        return;
    }

    std::cout << "Reading file: " << fileName << std::endl;

    // Set the total number of entries per line
    const int entriesPerLine = possibleDealerCards + 1;

    // Read and print each line from the CSV file
    std::string line;
    while (std::getline(file, line)) {
        std::cout << "NEW LINE: ";

        // Tokenize the line based on commas
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> values;

        while (std::getline(ss, token, ',')) {
            values.push_back(token);
        }

        // Check for entries per line exceeded or not met
        if (values.size() > entriesPerLine) {
            std::cerr << "Error: Entries per line exceeded. Ignoring extra entries." << std::endl;
            values.resize(entriesPerLine, "NULL");
        } else if (values.size() < entriesPerLine) {
            std::cerr << "Error: Entries per line not met. Adding 'NULL' for missing entries." << std::endl;
            values.resize(entriesPerLine, "NULL");
        }

        // Print the first value by itself
        if (!values.empty()) {
            std::cout << values[0];

            // Print the rest of the values (excluding the first value)
            for (size_t i = 1; i < values.size(); ++i) {
                std::cout << ", " << values[i];
            }
        }

        std::cout << std::endl;
    }

    // Close the file
    file.close();
}

void StrategyGuideHandler::PrintCurrentStrategy() {
    cout << "Printing the active strategy" << endl ;

    for (const auto& pair : strategy) {
        std::cout << pair.first << ": [";

        // Print each entry in the array
        for (const auto& entry : pair.second) {
            std::cout << entry << "/";
        }

        // Remove the trailing '/' and close the bracket
        std::cout << "\b]" << std::endl;
    }
}

bool StrategyGuideHandler::CheckForCSV(const string &fileName) {
    if (fileName.size() < 4 || fileName.substr(fileName.size() - 4) != ".csv") {
        std::cerr << "Error: Invalid file format. Please provide a .csv file." << std::endl;
        return false;
    }
    return true;
}

bool StrategyGuideHandler::CheckForValidDealerNumber(int dealerCard) {
    if(dealerCard < 0 || dealerCard > 9){
        std::cerr << "Invalid Dealer card. Must be between 2 and 11 (Ace)." <<  std::endl;
        return false;
    }
    return true;
}
