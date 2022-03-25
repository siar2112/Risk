#include "Player.h"
#include "Orders.h"
// #include "PlayerStrategies.h"
#include <algorithm> 
using namespace std;

class Order;
class OrdersList;
class PlayerStrategy;

Player::Player() {
	this->territories = vector<Territory*>();
	this->hand = new Hand();
	OrdersList* ol;
	this->ordersList = ol;
	// vector<Order*> o;
	// this->orders = o;
	this->name = "";
	this->id = idMaker;
	idMaker++;
	this->reinforcementsAvailable = this->territories.size() / 3; //number of reinforcements is number of territories owned / 3... 
	//TODO: ... plus the continent's control bonus value if all territories of a continent are owned.
	//TODO: reinforcemnts available should be minimum 3 per turn.
}

Player::Player(string name) {
	this->territories = vector<Territory*>();
	this->hand = new Hand();
	//OrdersList* ol= new OrdersList();
	this->ordersList = new OrdersList();
	// vector<Order*> o;
	// this->orders = o;
	this->name = name;
	this->id = idMaker;
	idMaker++;
	this->reinforcementsAvailable = this->territories.size() / 3; //number of reinforcements is number of territories owned / 3... 
	//TODO: ... plus the continent's control bonus value if all territories of a continent are owned.
	//TODO: reinforcemnts available should be minimum 3 per turn.
}

Player::Player(string name, PlayerStrategy* pStrategy) {
	this->setStrategy(pStrategy);
	this->territories = vector<Territory*>();
	this->hand = new Hand();
	//OrdersList* ol= new OrdersList();
	this->ordersList = new OrdersList();
	// vector<Order*> o;
	// this->orders = o;
	this->name = name;
	this->id = idMaker;
	idMaker++;
	this->reinforcementsAvailable = this->territories.size() / 3; //number of reinforcements is number of territories owned / 3... 
	//TODO: ... plus the continent's control bonus value if all territories of a continent are owned.
	//TODO: reinforcemnts available should be minimum 3 per turn.
}


Player::Player(vector<Territory*> territories, Hand* hand, OrdersList* ordersL, string name) {
	this->territories = territories;
	this->hand = hand;
	this->ordersList = ordersL;
	// vector<Order*> o;
	// this->orders = o;
	this->name = name;
	this->id = idMaker;
	idMaker++;
	this->reinforcementsAvailable = this->territories.size() / 3; //number of reinforcements is number of territories owned / 3... 
	//TODO: ... plus the continent's control bonus value if all territories of a continent are owned.
	//TODO: reinforcemnts available should be minimum 3 per turn.
}

Player::Player(const Player& toCopy) {
	this->territories = territories;
	// this->orders = toCopy.orders;
	this->ordersList = toCopy.ordersList;
	this->hand = toCopy.hand;
	this->name = toCopy.name;
	this->id = toCopy.id;
	this->reinforcementsAvailable = toCopy.reinforcementsAvailable;
}

//destructor
Player::~Player() {};

//outstream operator overloading
ostream& operator << (ostream& outputStream, const Player& p) {
	outputStream << "\n*****Player Info:*****" << endl;
	outputStream << "Name: " << p.name << endl;
	outputStream << "Hand: " << *(p.hand) << endl;
	// outputStream << "Orders: " << endl; //this isn't working because it uses functions from undefined OrdersList class
	// for(int i = 0; i<(*(p.ordersList)).size(); i++){ //vector iterator
	//     outputStream<<p.ordersList.at(i)<<", ";
	// }
	outputStream << "\nTerritories: " << endl;
	for (int i = 0; i < p.territories.size(); i++) { //vector iterator
		outputStream << p.territories.at(i)->getName() << ", ";
	}
	outputStream << endl;
	outputStream << "Id: " << p.id << endl;
	outputStream << "Reinforcements Available: " << p.reinforcementsAvailable << endl;
	return outputStream;
};

vector<Territory*> Player::toAttack() {
	return this->playerStrategy->toAttack();


	// //return a list of territories that are to be attacked
	// vector<Territory*> territoriesToAttack;
	// vector<int> territoryIDcounter;


	// //Get all egdes
	// for(int i=0; i<territories.size();i++){
	// 	for(int j=0;j<territories[i]->edges.size();j++){
	// 		//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
	// 		if(!(find(territoryIDcounter.begin(),territoryIDcounter.end(),territories[i]->edges[j]->getID())!=territoryIDcounter.end())){
	// 			//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
	// 			territoriesToAttack.push_back(territories[i]->edges[j]);
	// 			territoryIDcounter.push_back(territories[i]->edges[j]->getID());
	// 		}	
	// 	}
	// }

	// vector<int> PlayerterritoriesID;
	// for(int j=0;j<territories.size();j++){
	//     PlayerterritoriesID.push_back(territories[j]->getID()); 
	// }

	// cout<<"Here is the ID of your territories:"<<endl;
	//  for(int j=0;j<PlayerterritoriesID.size();j++){
	//     cout<<PlayerterritoriesID[j]<<endl;
	// }



	// //Remove edges that point to a territory owned by the player
	// for(int i=0;i<territoriesToAttack.size();i++){
	// 	if(find(PlayerterritoriesID.begin(),PlayerterritoriesID.end(),territoriesToAttack[i]->getID())!=PlayerterritoriesID.end()){
	// 		//cout<<territoriesToAttack[i]->getName()<<endl; debug helper
	// 		territoriesToAttack.erase(territoriesToAttack.begin()+i);
	// 		i-=1;
	// 	}
	// }

	// //Remove duplicates
	// //territoriesToAttack.erase( unique( territoriesToAttack.begin(), territoriesToAttack.end() ), territoriesToAttack.end() );
	// cout<<"Here are the territories that you can attack: "<<endl;
	// return territoriesToAttack;
};

vector<Territory*> Player::toDefend() { //return a list of territories that are to be defended
	return this->playerStrategy->toDefend();
};

void Player::issueOrder() { //implemented in GameEngine.cpp instead
	//creates an Order object and puts it in the player’s list of orders
	if (this->isNeutral) {
		cout << "Neutral player does not issue any orders." << endl;
		return;
	}
	else {
		playerStrategy->issueOrder();
	}
};

void Player::setTerritories(Territory* x) {
	//Territory*p=&x;

	this->territories.push_back(x);
};

vector<Territory*> Player::getOwnedTerit() {
	return this->territories;
};

void Player::setOwnedTerit(vector<Territory*> tv) {
	this->territories = tv;
};

int Player::getReinforce() {
	return this->reinforcementsAvailable;
};

void Player::setReinforce(int i) {
	this->reinforcementsAvailable = i;
};

int Player::getPlayerId() {
	return this->id;
};

vector<Player*> Player::getUnattackable() {
	return this->unattackable;
}

void Player::setUnattackable(vector<Player*> pv) {
	this->unattackable = pv;
};

void Player::setStrategy(PlayerStrategy* newStrategy) {
	this->playerStrategy = newStrategy;
};
