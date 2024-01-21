#include "StrategyGuideHandler.h"

#include <utility>

using namespace std;

// Constructor
StrategyGuideHandler::StrategyGuideHandler(const std::string& folderPath) {
    this->folderPath = folderPath;
    strategy = unordered_map< string, array<string, POSSIBLE_DEALER_CARDS>>();

    cout << "Created a strategy guide" << endl ;
}

// Destructor
StrategyGuideHandler::~StrategyGuideHandler() {
    //cout << "Deleting the strategy guide" << endl ;
}

//Load a guide into the useable strategy
void StrategyGuideHandler::loadGuide(const  string& csvFileName) {

    if(!isCSVFile(csvFileName)){
        return;
    }

    ifstream file(folderPath + csvFileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << csvFileName << "'" << endl;
        return;
    }

    const int ENTRIES_PER_LINE = POSSIBLE_DEALER_CARDS + 1;

    // Read and populate the  unordered_map
    string line;
    while (getline(file, line)) {

        istringstream ss(line);
        string token;
        vector<string> values;

        while (getline(ss,token,',')) {
            values.push_back(token);
        }

        // Check for entries per line not correct
        if (values.size() < ENTRIES_PER_LINE) {
            cerr << "Error: Entries per line not met. Adding 'Overflow' for missing entries." << endl;
            values.resize(ENTRIES_PER_LINE, "Overflow");
        }else if (values.size() > ENTRIES_PER_LINE) {
            cerr << "Error: Entries per line exceeded. Cutting off additional entries." << endl;
            values.resize(ENTRIES_PER_LINE, "Overflow");
        }

        string key = values[0];

        array<string, POSSIBLE_DEALER_CARDS> strategyArray;
        for (int i = 0; i < POSSIBLE_DEALER_CARDS; i++) {
            strategyArray[i] = values[i+1];
        }

        strategy[key] = strategyArray;
    }
    file.close();
}

void StrategyGuideHandler::saveGuide(const string& csvFileName) {

    if(!isCSVFile(csvFileName)){
        return;
    }

    ofstream file(folderPath + csvFileName);
    if (!file.is_open()) {
         cerr << "Error: Unable to open/create file '" << csvFileName << "'" <<  endl;
        return;
    }

    // Iterate through the stored strategy and save to the file
    for (const auto& pair : strategy) {
        file << pair.first;

        for (const auto& entry : pair.second) {
            file << "," << entry;
        }

        file << endl;
    }

    file.close();
}

basic_string<char> StrategyGuideHandler::getEntry(const string& playerCards, int dealerCard) {
    //Dealer can have a 2-11, but the indexes will correspond to 0-9
    dealerCard -= 2;

    if(!isValidDealerNumber(dealerCard))    {return "Not Valid Dealer Card";}

    // Check if the key exists in the strategy map
    auto it = strategy.find(playerCards);
    if (it != strategy.end()) {
        // Key found, modify the corresponding entry
        array< string, POSSIBLE_DEALER_CARDS>& arrayPtr = it->second;
        // Perform modification here, for example:
        return arrayPtr[dealerCard];
    } else {
        // Key not found, handle the error or add a new entry if needed
        cerr << "Entry not found for key: " << playerCards <<  endl;
    }

    return "L";
}

void StrategyGuideHandler::editEntry(const string& playerCards, int dealerCard, string newMove) {
    //Dealer can have a 2-11, but the indexes will correspond to 0-9
    dealerCard -= 2;

    if(!isValidDealerNumber(dealerCard)){ return;}

    // Check if the key exists in the strategy map
    auto it = strategy.find(playerCards);
    if (it != strategy.end()) {
        // Key found, modify the corresponding entry
        array< string, POSSIBLE_DEALER_CARDS>& arrayPtr = it->second;
        // Perform modification here, for example:
        arrayPtr[dealerCard] = move(newMove);
    } else {
        // Key not found, handle the error or add a new entry if needed
         cerr << "Entry not found for key: " << playerCards <<  endl;
        // Add new entry logic if required
        return;
    }

    //printCurrentStrategy();
}

[[maybe_unused]] void StrategyGuideHandler::printFile(const string &csvFileName) {

    if(!isCSVFile(csvFileName))    {return;}

    ifstream file(folderPath + csvFileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << csvFileName << "'" <<  endl;
        return;
    }

    // Set the total number of entries per line
    const int ENTRIES_PER_LINE = POSSIBLE_DEALER_CARDS + 1;

    // Read and print each line from the CSV file
    string line;
    while ( getline(file, line)) {
         cout << "NEW LINE: ";

        // Tokenize the line based on commas
        istringstream ss(line);
        string token;
        vector< string> values;

        while ( getline(ss, token, ',')) {
            values.push_back(token);
        }

        // Check for entries per line exceeded or not met
        if (values.size() > ENTRIES_PER_LINE) {
             cerr << "Error: Entries per line exceeded. Ignoring extra entries." <<  endl;
            values.resize(ENTRIES_PER_LINE, "Overflow");
        } else if (values.size() < ENTRIES_PER_LINE) {
             cerr << "Error: Entries per line not met. Adding 'Overflow' for missing entries." <<  endl;
            values.resize(ENTRIES_PER_LINE, "Overflow");
        }

        // Print the first value by itself
        if (!values.empty()) {
            cout << values[0];

            // Print the rest of the values (excluding the first value)
            for (size_t i = 1; i < values.size(); ++i) {
                cout << ", " << values[i];
            }
        }

        cout <<  endl;
    }

    // Close the file
    file.close();
}

[[maybe_unused]] void StrategyGuideHandler::printCurrentStrategy() {
    cout << "Printing the active strategy" << endl ;

    for (const auto& pair : strategy) {
         cout << pair.first << ": [";

        // Print each entry in the array
        for (const auto& entry : pair.second) {
             cout << entry << "/";
        }

        // Remove the trailing '/' and close the bracket
         cout << "\b]" <<  endl;
    }
}

bool StrategyGuideHandler::isCSVFile(const std::string &fileName) {
    if (fileName.size() < 4 || fileName.substr(fileName.size() - 4) != ".csv") {
         cerr << "Error: Invalid file format. Please provide a .csv file." <<  endl;
        return false;
    }
    return true;
}

bool StrategyGuideHandler::isValidDealerNumber(int dealerCard) const {
    if(dealerCard < 0 || dealerCard > 9){
         cerr << "Invalid Dealer card. Must be between 2 and 11 (Ace)." <<   endl;
        return false;
    }
    return true;
}
