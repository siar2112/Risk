#ifndef PlayerStrategies_h
#define PlayerStrategies_h

#pragma once
#include <iostream>
#include <vector>
#include <string>


using namespace std;
class Player;
class Territory;
class Order;
class AggressiveStrategy;
class NeutralStrategy;
class HumanStrategy;
class BenevolentStrategy;
class CheaterStrategy;

class PlayerStrategy {
private:


public:
    Player* playerOfStrategy;
    string strategyType;

    /*-----------Constructors-------------*/
    PlayerStrategy();
    PlayerStrategy(Player* p);
    PlayerStrategy(const PlayerStrategy& toCopy);


    //Assignment operators
    virtual PlayerStrategy& operator =(const PlayerStrategy& p);
    virtual PlayerStrategy& operator =(const AggressiveStrategy& p);
    virtual PlayerStrategy& operator =(const NeutralStrategy& p);
    virtual PlayerStrategy& operator =(const HumanStrategy& p);
    virtual PlayerStrategy& operator =(const CheaterStrategy& p);
    virtual PlayerStrategy& operator =(const BenevolentStrategy& p);

    /*------------Destructor----------------*/
    ~PlayerStrategy();

    /*------------Methods-------------------*/
    friend ostream& operator << (ostream& outputStream, const PlayerStrategy& p); //outstream overload
    virtual vector<Territory*> toAttack() = 0;
    virtual vector<Territory*> toDefend() = 0;
    virtual void issueOrder() = 0; //implemented in GameEngine.cpp
};

#endif
