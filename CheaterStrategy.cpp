#include "Player.h"
#include "CheaterStrategy.h"
#include <algorithm> 
using namespace std;

class Order;
class OrdersList;

CheaterStrategy::CheaterStrategy() {
	cout << "Cheater strategy created." << endl;
	strategyType = "CHEATER";
}

CheaterStrategy::CheaterStrategy(Player* p) {
	playerOfStrategy = p;
	strategyType = "CHEATER";
	cout << "Cheater strategy created for player " << p->name << endl;
}


CheaterStrategy::CheaterStrategy(const CheaterStrategy& toCopy) {
	this->playerOfStrategy = toCopy.playerOfStrategy;
	this->strategyType = toCopy.strategyType;
}

//destructor
CheaterStrategy::~CheaterStrategy() {};

//outstream operator overloading
ostream& operator << (ostream& outputStream, const CheaterStrategy& p) {
	outputStream << "\n*****Player Strategy Info:*****" << endl;
	outputStream << "Name: " << p.playerOfStrategy->name << endl;
	outputStream << "Strategy Type: " << p.strategyType << endl;
	return outputStream;
};

//Assignment operator overload
CheaterStrategy& CheaterStrategy::operator =(const CheaterStrategy& p) {
	this->strategyType = p.strategyType;
	this->playerOfStrategy = p.playerOfStrategy;
	return *this;
}

vector<Territory*> CheaterStrategy::toAttack() {
	//return a list of territories that are to be attacked
	vector<Territory*> territoriesToAttack;
	vector<int> territoryIDcounter;


	//Get all egdes
	for (int i = 0; i < playerOfStrategy->territories.size(); i++) {
		for (int j = 0; j < playerOfStrategy->territories[i]->edges.size(); j++) {
			//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
			if (!(find(territoryIDcounter.begin(), territoryIDcounter.end(), playerOfStrategy->territories[i]->edges[j]->getID()) != territoryIDcounter.end())) {
				//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
				territoriesToAttack.push_back(playerOfStrategy->territories[i]->edges[j]);
				territoryIDcounter.push_back(playerOfStrategy->territories[i]->edges[j]->getID());
			}
		}
	}

	vector<int> PlayerterritoriesID;
	for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
		PlayerterritoriesID.push_back(playerOfStrategy->territories[j]->getID());
	}

	cout << "Here is the ID of your territories:" << endl;
	for (int j = 0; j < PlayerterritoriesID.size(); j++) {
		cout << PlayerterritoriesID[j] << endl;
	}



	//Remove edges that point to a territory owned by the player
	for (int i = 0; i < territoriesToAttack.size(); i++) {
		if (find(PlayerterritoriesID.begin(), PlayerterritoriesID.end(), territoriesToAttack[i]->getID()) != PlayerterritoriesID.end()) {
			//cout<<territoriesToAttack[i]->getName()<<endl; debug helper
			territoriesToAttack.erase(territoriesToAttack.begin() + i);
			i -= 1;
		}
	}

	//Remove duplicates
	territoriesToAttack.erase(unique(territoriesToAttack.begin(), territoriesToAttack.end()), territoriesToAttack.end());
	cout << "Here are the territories that you can attack: " << endl;
	return territoriesToAttack;
};

vector<Territory*> CheaterStrategy::toDefend() { //return a list of territories that are to be defended
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

void CheaterStrategy::issueOrder() { //implemented in GameEngine.cpp
	Territory* source = new Territory();
	Territory* target = new Territory();
	int mostArmies = 0;
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
		if (source->getEdges().at(i)->owner != source->owner) {
			target = source->getEdges().at(i);
		}
	}
	//use constructor Advance(Player* p, Player* p2, Territory* source, Territory* target, int numToAdvance);
	Advance* a = new Advance(playerOfStrategy, target->ownerPlayer, source, target, 1);
	playerOfStrategy->ordersList->addOrder(a);
	cout << "Order confirmed, Cheater player will attack from " + source->toString() << endl;
};

