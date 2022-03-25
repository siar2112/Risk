#ifndef HumanStrategy_h
#define HumanStrategy_h

#pragma once;
#include "PlayerStrategies.h"


class HumanStrategy :public PlayerStrategy {

public:
    Player* playerOfStrategy;
    //string strategyType = "HUMAN";

    /*-----------Constructors-------------*/
    HumanStrategy();
    HumanStrategy(Player* p);
    HumanStrategy(const HumanStrategy& toCopy);

    //Assignment operator 
    virtual HumanStrategy& operator =(const HumanStrategy& p);

    /*------------Destructor----------------*/
    ~HumanStrategy();

    /*------------Methods-------------------*/
    friend ostream& operator << (ostream& outputStream, const HumanStrategy& p); //outstream overload
    vector<Territory*> toAttack() override;
    vector<Territory*>  toDefend() override;
    void issueOrder() override; //implemented in GameEngine.cpp
};

#endif;