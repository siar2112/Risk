#ifndef NeutralStrategy_h
#define NeutralStrategy_h

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "PlayerStrategies.h"
using namespace std;


class NeutralStrategy : public PlayerStrategy {
private:


public:
    Player* playerOfStrategy;
    //string strategyType = "NEUTRAL";

    /*-----------Constructors-------------*/
    NeutralStrategy();
    NeutralStrategy(Player* p);
    NeutralStrategy(const NeutralStrategy& toCopy);

    //Assignment operator
    virtual NeutralStrategy& operator =(const NeutralStrategy& p);

    /*------------Destructor----------------*/
    ~NeutralStrategy();

    /*------------Methods-------------------*/
    friend ostream& operator << (ostream& outputStream, const NeutralStrategy& p); //outstream overload
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder(); //implemented in GameEngine.cpp
};

#endif
