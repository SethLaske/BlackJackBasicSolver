#include "StrategyGuideHandler.h"

#include <utility>

using namespace std;

// Constructor
StrategyGuideHandler::StrategyGuideHandler() {
    strategy = unordered_map< string, array<string, POSSIBLE_DEALER_CARDS>>();
    lastResults = 0;
}

// Destructor
StrategyGuideHandler::~StrategyGuideHandler() {
}

void StrategyGuideHandler::loadStrategyGuide(const std::string &csvFileName) {
    StrategyGuideGenerator strategyGuideGenerator;

    if(StrategyGuideGenerator::isCSVFile(csvFileName)){

        size_t lastBackSlashPos = csvFileName.find_last_of('\\');

        if (lastBackSlashPos != string::npos) {
            string newFolderPath = csvFileName.substr(0, lastBackSlashPos+1);
            setNewFolder(newFolderPath);
        } else {
            cerr << "Invalid file path for loading a strategy guide." << endl;
        }
    }else{
        cerr << "Invalid .csv for loading a strategy guide." << endl;
    }

    strategy = strategyGuideGenerator.makeStrategyFromFile( csvFileName);
}

void StrategyGuideHandler::saveStrategyGuide(const std::string &csvFileName) {

    StrategyGuideGenerator strategyGuideGenerator;
    strategyGuideGenerator.saveStrategyToFile(folderPath + csvFileName, strategy);

}

basic_string<char> StrategyGuideHandler::getEntry(const string& playerCards, int dealerCard) {
    //Dealer can have a 2-11, but the indexes will correspond to 0-9
    dealerCard -= 2;

    if(!isValidDealerNumber(dealerCard))    {return "Not Valid Dealer Card";}

    // Check if the key exists in the strategy map
    auto it = strategy.find(playerCards);
    if (it != strategy.end()) {

        array< string, POSSIBLE_DEALER_CARDS>& arrayPtr = it->second;
        return arrayPtr[dealerCard];
    } else {
        // Key not found, handle the error or add a new entry if needed
        cerr << "Entry not found for key: " << playerCards <<  endl;
    }

    return "L";
}

/*void StrategyGuideHandler::editEntry(const string& playerCards, int dealerCard, string newMove) {
    //Dealer can have a 2-11, but the indexes will correspond to 0-9
    dealerCard -= 2;

    if(!isValidDealerNumber(dealerCard)){ return;}

    // Check if the key exists in the strategy map
    auto it = strategy.find(playerCards);
    if (it != strategy.end()) {
        array< string, POSSIBLE_DEALER_CARDS>& arrayPtr = it->second;
        arrayPtr[dealerCard] = std::move(newMove);
    } else {
         cerr << "Entry not found for key: " << playerCards <<  endl;
        return;
    }
    //printCurrentStrategy();
}*/

[[maybe_unused]] void StrategyGuideHandler::printFile(const string &csvFileName) {

    if(!StrategyGuideGenerator::isCSVFile(csvFileName))    {return;}

    ifstream file(csvFileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << csvFileName << " while printing" <<  endl;
        return;
    }

    const int ENTRIES_PER_LINE = POSSIBLE_DEALER_CARDS + 1;

    string line;
    while ( getline(file, line)) {
         cout << "NEW LINE: ";

        istringstream ss(line);
        string token;
        vector< string> values;

        while ( getline(ss, token, ',')) {
            values.push_back(token);
        }

        if (values.size() > ENTRIES_PER_LINE) {
             cerr << "Error: Entries per line exceeded. Ignoring extra entries." <<  endl;
            values.resize(ENTRIES_PER_LINE, "Overflow");
        } else if (values.size() < ENTRIES_PER_LINE) {
             cerr << "Error: Entries per line not met. Adding 'Overflow' for missing entries." <<  endl;
            values.resize(ENTRIES_PER_LINE, "Overflow");
        }

        if (!values.empty()) {
            cout << values[0];

            for (size_t i = 1; i < values.size(); ++i) {
                cout << ", " << values[i];
            }
        }

        cout <<  endl;
    }

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

bool StrategyGuideHandler::isValidDealerNumber(int dealerCard) const {
    if(dealerCard < 0 || dealerCard > 9){
         cerr << "Invalid Dealer card. Must be between 2 and 11 (Ace)." <<   endl;
        return false;
    }
    return true;
}

void StrategyGuideHandler::saveResults(float results) {
    if (folderPath.empty()) {
        std::cerr << "Error: Folder path is empty." << std::endl;
        return;
    }

    std::string filePath = folderPath + "Results.txt";

    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open/create file '" << filePath << " while saving" << std::endl;
        return;
    }

    file.clear();
    file.seekp(0, std::ios::beg);

    file << results;

    file.close();
}

void StrategyGuideHandler::setNewFolder(const string &folderPath) {
    this->folderPath = folderPath;
}

void StrategyGuideHandler::updateResults(float results) {
    lastResults = results;
}

float StrategyGuideHandler::getResults() const {
    return lastResults;
}
