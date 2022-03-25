#ifndef GameEngine_h
#define GameEngine_h

#pragma once

#include "CommandProcessing.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "PlayerStrategies.h"
#include "HumanStrategy.h"
#include "NeutralStrategy.h"
#include "CheaterStrategy.h"
#include "AggressiveStrategy.h"
#include "BenevolentStrategy.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <random>
#include <regex>
#include <algorithm>

using namespace std;
//all class we have
class Map;
class MapLoader;
class Player;
class Card;
class Orders;
class OrdersList;
class Territory;
class Continent;
class Deck;
class Hand;

class GameEngine {

public:
    CommandProcessor cp; //GameEngine must use a Command Processor for getting input commands
    //default construction
    GameEngine();
    //copy constuction
    GameEngine(const GameEngine& GE);
    GameEngine& operator = (const GameEngine& GE);
    friend std::ostream& operator<<(std::ostream& stream, const GameEngine& g);
    std::string input;
    int state;
    // friend int getState();
    friend class CommandProcessing; //to allow CommandProcessing access to GameEngine state
    /*
    * state 0 = Start();
    *       1 = MapLoaded();
    *       2 = MapValidated();
    *       3 = PlayersAdded();
    *       4 = AssignReinforcement();
    *       5 = IssueOrders();
    *       6 = ExecuteOrders();
    *       7 = Win();
    */

    //step from requirement
    void Start();
    void MapLoaded();
    void MapValidated();
    void PlayersAdded();
    void AssignReinforcement();
    void IssueOrders();
    void ExecuteOrders();
    void Win();
    //for running program
    void Loop();

    //Assignment 2:
    void StartUpPhase();
    Map* mainMap;
    vector <Player*> Players;
    Deck gameDeck;
    void tesGame();
    bool testWinning();

};

#endif
