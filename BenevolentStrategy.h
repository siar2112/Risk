#ifndef BenevlolentStrategy_h
#define BenevolentStrategy_h

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "PlayerStrategies.h"
using namespace std;


class BenevolentStrategy : public PlayerStrategy {
private:


public:
    Player* playerOfStrategy;
    //string strategyType;

    /*-----------Constructors-------------*/
    BenevolentStrategy();
    BenevolentStrategy(Player* p);
    BenevolentStrategy(const BenevolentStrategy& toCopy);

    //Assignment operator
    virtual BenevolentStrategy& operator =(const BenevolentStrategy& p);

    /*------------Destructor----------------*/
    ~BenevolentStrategy();

    /*------------Methods-------------------*/
    friend ostream& operator << (ostream& outputStream, const BenevolentStrategy& p); //outstream overload
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder(); //implemented in GameEngine.cpp instead

};

#endif


