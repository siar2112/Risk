#ifndef AggressiveStrategy_h
#define AggressiveStrategy_h

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "PlayerStrategies.h"
using namespace std;


class AggressiveStrategy : public PlayerStrategy {
private:


public:
    Player* playerOfStrategy;
    //string strategyType;

    /*-----------Constructors-------------*/
    AggressiveStrategy();
    AggressiveStrategy(Player* p);
    AggressiveStrategy(const AggressiveStrategy& toCopy);

    //Assignment operator
    virtual AggressiveStrategy& operator =(const AggressiveStrategy& p);

    /*------------Destructor----------------*/
    ~AggressiveStrategy();

    /*------------Methods-------------------*/
    friend ostream& operator << (ostream& outputStream, const AggressiveStrategy& p); //outstream overload
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder(); //implemented in GameEngine.cpp instead

};

#endif
