#include "Player.h"
#include "BenevolentStrategy.h"
#include <algorithm> 
using namespace std;

class Order;
class OrdersList;

BenevolentStrategy::BenevolentStrategy() {
	cout << "Benevolent strategy created." << endl;
	strategyType = "BENEVOLENT";
	cout << "No player is associated with this BENEVOLENT strategy" << endl;
}

BenevolentStrategy::BenevolentStrategy(Player* p) {
	this->playerOfStrategy = p;
	strategyType = "BENEVOLENT";
	cout << "BENEVOLENT strategy created for player " << p->name << endl;
}


BenevolentStrategy::BenevolentStrategy(const BenevolentStrategy& toCopy) {
	this->playerOfStrategy = toCopy.playerOfStrategy;
	this->strategyType = toCopy.strategyType;
}

//destructor
BenevolentStrategy::~BenevolentStrategy() {};

//outstream operator overloading
ostream& operator << (ostream& outputStream, const BenevolentStrategy& p) {
	outputStream << "\n*****Player Strategy Info:*****" << endl;
	outputStream << "Name: " << p.playerOfStrategy->name << endl;
	outputStream << "Strategy Type: " << p.strategyType << endl;
	return outputStream;
};

//Assignment operator overload
BenevolentStrategy& BenevolentStrategy::operator =(const BenevolentStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}

vector<Territory*> BenevolentStrategy::toAttack() { //return a list of territories that are to be attacked
	vector<int> PlayerterritoriesID;
	vector<Territory*> territoriesToAttack;

	cout << "Benevolent player does not attak." << endl;

	return territoriesToAttack;
};

vector<Territory*> BenevolentStrategy::toDefend() { //return a list of territories that are to be defended
	vector<int> PlayerterritoriesID;
	vector<Territory*> territoriesToDefend;

	Territory* begin = *playerOfStrategy->territories.begin();
	int low = begin->getSoliders();

	for (auto it = playerOfStrategy->territories.begin(); it != playerOfStrategy->territories.end(); it++) {
		if ((*it)->getSoliders() < low) {
			low = (*it)->getSoliders();
		}
	}

	for (auto it = playerOfStrategy->territories.begin(); it != playerOfStrategy->territories.end(); it++) {
		if ((*it)->getSoliders() == low) {
			territoriesToDefend.push_back(*it);
		}
	}
	
	return territoriesToDefend;
};

void BenevolentStrategy::issueOrder() {
	Territory* source = new Territory();
	Territory* target = new Territory();
	int mostArmies = 0;
	bool isAbleToReinforce = false;
	//find owned territory with most armies
	for (int i = 0; i < (playerOfStrategy->getOwnedTerit()).size(); i++) {
		if (playerOfStrategy->territories.at(i)->getSoliders() > mostArmies) {
			mostArmies = playerOfStrategy->territories.at(i)->getSoliders();
			source = playerOfStrategy->territories.at(i);
		}
	}
	//find info for a neighbouring territory to use in Advance constructor
	for (int i = 0; i < source->getEdges().size(); i++) {
		//verify target isn't owned by attacking player
		if (source->getEdges().at(i)->owner == source->owner) {
			target = source->getEdges().at(i);
			isAbleToReinforce = true;
		}
	}

	if (isAbleToReinforce) {
		//use constructor Advance(Player* p, Player* p2, Territory* source, Territory* target, int numToAdvance);
		Advance* a = new Advance(playerOfStrategy, target->ownerPlayer, source, target, mostArmies - 1);
		playerOfStrategy->ordersList->addOrder(a);
		cout << "Order confirmed, Benevolent player will prepare to defend " + target->toString() << endl;
	}
	else {
		cout << "Benevolent player can't move his soliders for defence for now" << endl;
		// If he can't advance, he should use a REINFORCE order if he has it in his orderlist
	}
};