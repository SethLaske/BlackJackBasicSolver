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

    static std::string toString();

    //Dev Variables
    //Switch to true to see the results of a trial
    inline static const bool DISPLAYRESULTS = false;
    //Switch to true to show individual trial progress - only use for long trials, and probably never when running GA
    inline static const bool DISPLAYTRIALSPROGRESS = false;
    inline static const int TRIALPROGRESSINCREMENTS = 20;
    //Switch to true to see how a game progresses - only use for individual games
    inline static const bool DISPLAYGAMEINPROGRESS = false;

    //Switch to true to show Genetic progress
    inline static const bool DISPLAYGENETICALGORITHMPROGRESS = true;
    inline static const int GENETICALGORITHMPROGRESSINCREMENTS = 10;
};




#endif //HOUSERULES_H
