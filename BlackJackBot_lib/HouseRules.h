//
// Created by small on 1/18/2024.
//

#ifndef HOUSERULES_H
#define HOUSERULES_H

#include "iostream"

class HouseRules {
public:
    inline static const float BLACKJACKPAYOUTRATE = (3.0/2.0);  //If the computer loses precision on 3/2 thats not my fault
    inline static const int NUMBEROFDECKSINSHOE = 4;
    inline static const float MINPENETRATIONPERCENT = .4f;
    inline static const float MAXPENETRATIONPERCENT = .6f;
    inline static const bool IGNOREDEBT = true;

    const static std::string toString();
};




#endif //HOUSERULES_H
