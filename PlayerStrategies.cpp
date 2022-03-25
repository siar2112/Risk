#include "Player.h"
#include "PlayerStrategies.h"
#include "AggressiveStrategy.h"
#include "NeutralStrategy.h"
#include "HumanStrategy.h"
#include "CheaterStrategy.h"
#include "BenevolentStrategy.h"
#include <algorithm> 
using namespace std;

class Order;
class OrdersList;

PlayerStrategy::PlayerStrategy() {
	cout << "New strategy created." << endl;
}

PlayerStrategy::PlayerStrategy(Player* p) {
	this->playerOfStrategy = p;
	cout << "Strategy created for player " << p->name << endl;
}


PlayerStrategy::PlayerStrategy(const PlayerStrategy& toCopy) {
	this->playerOfStrategy = toCopy.playerOfStrategy;
	this->strategyType = toCopy.strategyType;
}

//Assignment operator overloads for self and subclasses
PlayerStrategy& PlayerStrategy::operator =(const PlayerStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}


//subclasses
PlayerStrategy& PlayerStrategy::operator =(const AggressiveStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}

PlayerStrategy& PlayerStrategy::operator =(const NeutralStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}


PlayerStrategy& PlayerStrategy::operator =(const HumanStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}

PlayerStrategy& PlayerStrategy::operator =(const CheaterStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}

PlayerStrategy& PlayerStrategy::operator =(const BenevolentStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}

//destructor
PlayerStrategy::~PlayerStrategy() {};

//outstream operator overloading
ostream& operator << (ostream& outputStream, const PlayerStrategy& p) {
	outputStream << "\n*****Player Strategy Info:*****" << endl;
	outputStream << "Name: " << p.playerOfStrategy->name << endl;
	outputStream << "Strategy Type: " << p.strategyType << endl;
	return outputStream;
};