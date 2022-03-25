
#include "Player.h"
#include "HumanStrategy.h"
using namespace std;




HumanStrategy::HumanStrategy() {
    cout << "Human strategy created." << endl;
    strategyType = "HUMAN";
    cout << "No player is associated with this Human strategy" << endl;
}


HumanStrategy::HumanStrategy(Player* p) {
    cout << "Human strategy created." << endl;
    playerOfStrategy = p;

}



HumanStrategy::HumanStrategy(const HumanStrategy& toCopy) {
    this->playerOfStrategy = toCopy.playerOfStrategy;
    this->strategyType = toCopy.strategyType;
}




//destructor
HumanStrategy::~HumanStrategy() {};

//outstream operator overloading
ostream& operator << (ostream& outputStream, const HumanStrategy& p) {
    outputStream << "\n*****Player Strategy Info:*****" << endl;
    outputStream << "Name: " << p.playerOfStrategy->name << endl;
    outputStream << "Strategy Type: " << p.strategyType << endl;
    return outputStream;
};


//Assignment operator overload
HumanStrategy& HumanStrategy::operator =(const HumanStrategy& p) {
    this->strategyType = p.strategyType;
    this->playerOfStrategy = p.playerOfStrategy;
    return *this;
}



vector<Territory*> HumanStrategy::toAttack() {

    // //return a list of territories that are to be attacked
    vector<Territory*> territoriesToAttack;
    vector<int> territoryIDcounter;


    //Get all egdes
    for (int i = 0; i < playerOfStrategy->territories.size(); i++) {
        for (int j = 0; j < playerOfStrategy->territories[i]->edges.size(); j++) {
            // 		//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
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

    /*cout<<"Here is the ID of your territories:"<<endl;
    for(int j=0;j<PlayerterritoriesID.size();j++){
        cout<<PlayerterritoriesID[j]<<endl;
    }*/ //Debugging purposes



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
    //cout<<"Here are the territories that you can attack: "<<endl;
    return territoriesToAttack;
}


vector<Territory*>HumanStrategy::toDefend() {
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
}


void HumanStrategy::issueOrder() {
    string input;
    cout << "It's your turn " + playerOfStrategy->name + "?" << endl;
    cout << "enter (yes) for issue the order" << endl;
    cin >> input;
    if (input == "yes") {
        string orderInput;
        bool isRightOrder = true;
        while (isRightOrder) { //while loop to make sure the player enter a right order

            cout << "What order will you use, " + playerOfStrategy->name + " ?" << endl;
            string orderInput;
            cin >> orderInput;
            cout << playerOfStrategy->name << " used " << orderInput << "!" << endl;
            //this is where card.play() would be used if it worked 
            if (orderInput == "ADVANCE") {
                // Player a = Players[i]; //player using order
                // Player b; //player being attacked

                Territory* start;
                Territory* finish;
                int armies;
                Player* secondplayer;

                //Territory start
                bool key = true;
                while (key) {
                    cout << "Please enter the ID of territory to advance from:" << endl;
                    int terr1;
                    cin >> terr1;
                    for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                        if (playerOfStrategy->territories[j]->getID() == terr1) {
                            start = playerOfStrategy->territories[j];
                            key = false;
                        }
                    }

                    if (key) {
                        cout << "Wrong input, you have no territories with ID " + terr1 << endl;
                        cout << "Here is the list of all your territories:\n";
                        for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                            cout << playerOfStrategy->territories[j]->toString() << endl;
                        }
                    }
                }


                //Territory finish
                key = true;
                while (key) {
                    cout << "Please the ID of the territory that you want to advance to" << endl;
                    cout << (*start).showEdges() << endl;
                    int terr1;
                    cin >> terr1;
                    for (int j = 0; j < (*start).edges.size(); j++) {
                        if ((*start).edges[j]->getID() == terr1) {
                            finish = (*start).edges[j];
                            key = false;
                        }
                    }

                    if (key) {
                        cout << "Wrong input, you can't advance to territory number " + terr1 << endl;
                        cout << "Please re-enter your input: " << endl;
                    }
                }

                //num of Armies

                cout << "Please enter number of armies to advance: " << endl;
                int armiesIn;
                cin >> armiesIn;
                cout << "Ok. " << armiesIn << " soliders." << endl;
                cout << "These soliders will advance in the order execution phase." << endl;

                //second player
                secondplayer = finish->ownerPlayer;

                // Adding order to order list
                Advance* inputOrder = new Advance(playerOfStrategy, secondplayer, start, finish, armiesIn);
                (*playerOfStrategy).ordersList->addOrder(inputOrder);
                isRightOrder = false;

            }

            if (orderInput == "DIPLOMACY") {

                //finding second player
                Player* playerB;
                cout << "Please enter name of player to Negotiate with (Must be a player that is in your edge): " << endl;
                string namePlayerB;
                cin >> namePlayerB;
                int z = 0;
                for (z; z < playerOfStrategy->getOwnedTerit().size(); z++) { //Players[z] will be player being negotiated with
                    for (int k = 0; k < playerOfStrategy->getOwnedTerit()[z]->edges.size(); k++) {
                        if (namePlayerB == playerOfStrategy->getOwnedTerit()[z]->edges[k]->owner) {
                            playerB = playerOfStrategy->getOwnedTerit()[z]->edges[k]->ownerPlayer;
                        }
                    }
                }

                //Adding order to order list
                Negotiate* inputOrder = new Negotiate(playerOfStrategy, playerB);
                playerOfStrategy->ordersList->addOrder(inputOrder);
                isRightOrder = false;

                cout << "Order added, it will be executing in the next phase" << endl;
            }

            if (orderInput == "BLOCKADE") {
                //finding territory
                Territory* terrToBlockade;
                cout << "Please enter ID of territory to Blockade: " << endl;
                int terr1;
                cin >> terr1;
                for (int z = 0; z < playerOfStrategy->territories.size(); z++) {
                    if (playerOfStrategy->territories.at(z)->getID() == terr1) {
                        cout << "Ok. Territory " << playerOfStrategy->territories.at(z)->getName() << endl;
                        terrToBlockade = playerOfStrategy->territories.at(z);
                    }
                }
                Blockade* inputOrder = new Blockade(playerOfStrategy, terrToBlockade);
                playerOfStrategy->ordersList->addOrder(inputOrder);
                cout << "Order added, it will be executing in the next phase" << endl;
                isRightOrder = false;
            }

            if (orderInput == "BOMB") {
                Territory* toBomb;
                bool key = true;
                while (key) {
                    cout << "Please enter the ID of the territory that you want to bomb (Must be in the territories that you can attack) " << endl;
                    int terr1;
                    cin >> terr1;
                    for (int j = 0; j < toAttack().size(); j++) {
                        if ((toAttack()[j]->getID() == terr1)) {
                            toBomb = toAttack()[j];
                            key = false;
                        }
                    }
                    if (key) {
                        cout << "Wrong input, you can't attack territory number " + terr1 << endl;
                        cout << "Please re-enter your input: " << endl;
                    }
                }
                Bomb* inputOrder = new Bomb(playerOfStrategy, toBomb);
                cout << "Bomb created" << endl;
                playerOfStrategy->ordersList->addOrder(inputOrder);
                cout << "Bomb will be dropped in the next phase" << endl;
                isRightOrder = false;
            }

            if (orderInput == "AIRLIFT") {

                Territory* start;
                Territory* finish;
                int armies;


                //Territory start
                bool key = true;
                while (key) {
                    cout << "Please enter ID of territory to advance from:" << endl;
                    int terr1;
                    cin >> terr1;
                    for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                        if (playerOfStrategy->territories[j]->getID() == terr1) {
                            start = playerOfStrategy->territories[j];
                            key = false;
                            break;
                        }
                    }
                    if (key) {
                        cout << "Wrong input, you have no territories number  " + terr1 << endl;
                        cout << "Here is the list of all your territories: " << endl;
                        for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                            cout << playerOfStrategy->territories[j]->toString() << endl;
                        }
                    }
                }


                //Territory finish
                key = true;
                while (key) {
                    cout << "Please enter ID of territory that you want to advance to: " << endl;
                    int terr1;
                    cin >> terr1;
                    for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                        if (playerOfStrategy->territories[j]->getID() == terr1) {
                            finish = playerOfStrategy->territories[j];
                            key = false;
                        }
                    }
                    if (key) {
                        cout << "Wrong input, you have no territories number  " + terr1 << endl;
                        cout << "Here is the list of all your territories: ";
                        for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                            cout << playerOfStrategy->territories[j]->toString() << endl;
                        }
                    }
                }

                //Num of armies
                cout << "Please enter number of armies to advance: " << endl;
                cin >> armies;
                cout << "Ok. " << armies << " soliders." << endl;
                cout << "These soliders will be transported in the order execution phase." << endl;


                Airlift* inputOrder = new Airlift(playerOfStrategy, start, finish, armies);
                playerOfStrategy->ordersList->addOrder(inputOrder);
                isRightOrder = false;

            }

            if (orderInput == "REINFORCEMENT") {
                Territory* target;
                //Soliders to be deployed
                cout << "Here are the soliders you have in backup: " + to_string(playerOfStrategy->getReinforce()) << endl;
                bool key = true;
                int numberOfSoliders = 0;
                while (key) {
                    cout << " Enter how many soliders you want to assign" << endl;
                    cin >> numberOfSoliders;
                    if (numberOfSoliders > playerOfStrategy->getReinforce()) {
                        cout << "You are trying to assign more soliders than you, please re-enter your input " << endl;
                    }
                    else {
                        break;
                    }
                }

                //Finding which territory he want to reinforce
                int InputID;
                cout << "Here is all your territories: " << endl;
                for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                    cout << playerOfStrategy->territories[j]->toString() << endl;
                }
                cout << "Please enter the territory ID that you want to reinforce" << endl;
                cin >> InputID;

                for (int j = 0; j < playerOfStrategy->territories.size(); j++) {
                    if (InputID == playerOfStrategy->territories[j]->getID()) {
                        target = playerOfStrategy->territories[j];
                    }
                }

                Deploy* inputOrder = new Deploy(playerOfStrategy, target, numberOfSoliders);
                playerOfStrategy->ordersList->addOrder(inputOrder);
                isRightOrder = false;
            }
            if (isRightOrder) {
                cout << "Wrong order input there no orders " + orderInput + "\nPlease re-enter your input" << endl;
            }
        }
    }
    else {
        cout << playerOfStrategy->name + " skipped his turn" << endl;
    }
    cout << "order confirmed!" << endl;
}
