#ifndef CheaterStrategy_h
#define CheaterStrategy_h

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "PlayerStrategies.h"
using namespace std;


class CheaterStrategy : public PlayerStrategy {
private:


public:
    Player* playerOfStrategy;
    //string strategyType = "CHEATER";

    /*-----------Constructors-------------*/
    CheaterStrategy();
    CheaterStrategy(Player* p);
    CheaterStrategy(const CheaterStrategy& toCopy);

    //Assignment operator
    virtual CheaterStrategy& operator =(const CheaterStrategy& p);

    /*------------Destructor----------------*/
    ~CheaterStrategy();

    /*------------Methods-------------------*/
    friend ostream& operator << (ostream& outputStream, const CheaterStrategy& p); //outstream overload
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder() override;
};

#endif

