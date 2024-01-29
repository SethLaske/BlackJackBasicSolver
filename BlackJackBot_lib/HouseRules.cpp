#include "HouseRules.h"

std::string HouseRules::toString() {
    std::string returnString = "***HOUSE RULES***";
    returnString += "\n Blackjack payout: " + std::to_string(BLACKJACKPAYOUTRATE);
    returnString += "\n Number of decks: " + std::to_string(NUMBEROFDECKSINSHOE);
    returnString += "\n Min penetration: " + std::to_string(MINPENETRATIONPERCENT);
    returnString += "\n Max penetration: " + std::to_string(MAXPENETRATIONPERCENT);
    returnString += "\n Ignore debt: " + std::to_string(IGNOREDEBT);


    return returnString;
}