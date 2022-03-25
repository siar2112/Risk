#include "Player.h"
#include "NeutralStrategy.h"
#include <algorithm> 
using namespace std;

class Order;
class OrdersList;

NeutralStrategy::NeutralStrategy() {
	cout << "Neutral strategy created." << endl;
	this->strategyType = "NEUTRAL";
	cout << " No player is associated with this Neutral strategy" << endl;
}

NeutralStrategy::NeutralStrategy(Player* p) {
	this->playerOfStrategy = p;
	this->strategyType = "NEUTRAL";
	cout << "Neutral strategy created for player " << p->name << endl;
}


NeutralStrategy::NeutralStrategy(const NeutralStrategy& toCopy) {
	this->playerOfStrategy = toCopy.playerOfStrategy;
	this->strategyType = toCopy.strategyType;
}

//destructor
NeutralStrategy::~NeutralStrategy() {};

//outstream operator overloading
ostream& operator << (ostream& outputStream, const NeutralStrategy& p) {
	outputStream << "\n*****Player Strategy Info:*****" << endl;
	outputStream << "Name: " << p.playerOfStrategy->name << endl;
	outputStream << "Strategy Type: " << p.strategyType << endl;
	return outputStream;
};

//Assignment operator overload
NeutralStrategy& NeutralStrategy::operator =(const NeutralStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}

vector<Territory*> NeutralStrategy::toAttack() {
	cout << "Neutral player does not attack." << endl;
	vector<Territory*> emptyVector;
	return emptyVector;
};

vector<Territory*> NeutralStrategy::toDefend() { //return a list of territories that are to be defended
	vector<int> PlayerterritoriesID;
	vector<Territory*> territoriesToDefend;

	//vector of ID of the territory that the player own
	for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
		PlayerterritoriesID.push_back(playerOfStrategy->territories[j]->getID());
	}

	//Verify if a territory has an enemy territory in its egdes
	for (int i = 0; i < playerOfStrategy->territories.size(); i++) {
		bool edgesOutside = false;
		for (int j = 0; j < playerOfStrategy->territories[i]->edges.size(); j++) {
			if (!(find(PlayerterritoriesID.begin(), PlayerterritoriesID.end(), playerOfStrategy->territories[i]->edges[j]->getID()) != PlayerterritoriesID.end())) {
				edgesOutside = true;
			}
		}
		if (edgesOutside) {
			territoriesToDefend.push_back(playerOfStrategy->territories[i]);
		}
	}
	return territoriesToDefend;
};

void NeutralStrategy::issueOrder() { //implemented in GameEngine.cpp
									//Neutral player doesn't issue orders, so this is never used
	cout << "Neutral doesn't want to fight" << endl;	//Neutral player becomes Aggressive if gets Advanced from someone,
													//The code for that is implemented in Order.cpp
};

