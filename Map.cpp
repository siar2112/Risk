// #pragma once
#include <iostream>
#include<fstream>
#include <vector>
#include<cstdlib>
#include<string>
#include <sstream>
#include "Map.h"
using namespace std;


// function of player class
// Player::Player(string x, int y){
//     this->playerName=x;
//     this->playerID=y;
// }

// Player::Player(){
//     this->playerName="No name";
// }

// string Player:: getPName(){
//     return playerName;
// }

// void Player::setPName(string x){
//     this->playerName=x;
// }

// string Player::toString(){
//   string x= "Player Name: "+this->playerName+"  ID:" +std::to_string(this->playerID);
//   return x;
// }

// method of Territory class

Territory::Territory(int id, string name, vector<Territory*> edges, int soliders) {
    this->territoryID = id;
    this->territoryName = name;
    this->edges = *new vector<Territory*>(edges); // not sure
    //this->edges=edges;
    // this->owner=owner;
    this->numberOfSolider = soliders;
}

Territory::Territory() {
    this->territoryID = 0;
    this->territoryName = "null";
    this->edges; // not sure
    this->numberOfSolider = 0;
}

Territory::Territory(int id, string name) {
    this->territoryID = id;
    this->territoryName = name;
    this->numberOfSolider = 0;
    this->edges; // not sure
}

Territory::Territory(const Territory& e) {
    this->territoryID = *new int(e.territoryID);
    this->territoryName = *new string(e.territoryName);
    this->edges = *new vector<Territory*>(e.edges);
    this->numberOfSolider = *new int(e.numberOfSolider);
}

// getMethod
int Territory::getID() {
    return territoryID;
};

string Territory::getName() {
    return territoryName;
};

int Territory::getSoliders() {
    return numberOfSolider;
};

vector<Territory*> Territory::getEdges() {
    return edges;
};

// Player Territory:: getPlayer(){
//     return owner;
// }

void Territory::setSoliders(int x) {
    this->numberOfSolider = x;
};

void Territory::setEdges(Territory* x) {
    //Territory* p=&x;
    //cout<< (*p).getName()<<endl;
    edges.push_back(x);
    /*for(int i=0;i< edges.size();i++){
       cout<< (*edges[i]).getName()<<endl;
    }*/

};

string Territory::toString() {
    string x = "Territory ID:" + std::to_string(territoryID) + " || Territory Name: " + territoryName
        + "  -> Number of soliders: " + std::to_string(numberOfSolider) + " || Owner: " + owner;
    return x;
};

string Territory::showEdges() {
    string x = "\nHere are the edges of " + territoryName + "\n";
    for (int i = 0; i < edges.size(); i++) {
        x = x + std::to_string(i + 1) + " : Territory ID: " + std::to_string((*edges[i]).getID())
            + "-> Name: " + (*edges[i]).getName() + " -> Owner: " + (*edges[i]).owner + "\n";
    }
    return x;
};

//Continent class

//Constructor
Continent::Continent() {
    c_countries;
    continentName = "null";

}

Continent::Continent(string x) {
    continentName = x;

}

Continent::Continent(string x, vector<Territory*> y) {
    c_countries = *new vector<Territory*>(y);
    continentName = x;

}

//copy Constructor

Continent::Continent(const Continent& e) {
    this->continentName = *new string(e.continentName);
    this->c_countries = *new vector<Territory*>(e.c_countries);
}

void Continent::setTerritories(Territory* x) {
    c_countries.push_back(x);
};



string Continent::toString() {
    string x = "\nHere are the list of countries inside continent " + continentName + "\n\n";

    for (int i = 0; i < c_countries.size(); i++) {
        x = x + (*c_countries[i]).toString() + "\n";
    };

    return x;
};

bool Continent::eularianMap() {
    vector<int> degrees(c_countries.size());

    int countOdds = 0;

    for (int i = 0; i < c_countries.size(); i++) {
        cout << to_string((*c_countries[i]).getEdges().size()) << endl;
        degrees[i] = (*c_countries[i]).getEdges().size();
    }

    for (auto d : degrees) {
        if (d % 2 == 1) {
            countOdds++;
        }
    }
    return(countOdds == 0 || countOdds == 2);
};

//Map

//Constructor

Map::Map() {
    mapName = "null";
    world;
    continents;
}

Map::Map(string name, vector<Territory*> world, vector<Continent*> continents) {
    mapName = name;
    this->world = *new vector<Territory*>(world);
    this->continents = *new vector<Continent*>(continents);
}

//Copy Constructor

Map::Map(const Map& e) {
    this->mapName = *new string(e.mapName);
    this->world = *new vector<Territory*>(e.world);
    this->continents = *new vector<Continent*>(e.continents);
}

vector<Territory*> Map::getWorld() {
    return world;
};

string Map::getMapName() {
    return mapName;
};

string Map::toString() {
    string x = "\nHERE IS THE INFO OF THE WORLD: " + mapName + "\n=======================\n";
    for (int i = 0; i < continents.size(); i++) {
        x = x + (*continents[i]).toString();
    }
    return x;
};

bool Map::isAValidMap() {
    bool x = true;
    cout << "Proceeding verification of every continent" << endl;
    for (int i = 0; i < continents.size(); i++) {
        if (!(*continents[i]).eularianMap()) {
            x = false;
            break;
        }
        cout << "Continent: " + (*continents[i]).continentName + " is an eularian subgraph" << endl;
    }
    if (x) {

    }
    return x;
};


//Map loader class:



MapLoader::MapLoader(string x) {
    this->fileName = x;
    string nameWorld;
    cout << "Please enter the name of your map: ";
    cin >> nameWorld;
    vector<Continent*> continents;
    vector<Territory*> territories;
    vector<string> lines;
    //vector<Territory*> pointers;
    ifstream fileStream;
    fileStream.open(x);

    if (!fileStream.is_open()) {
        cout << " FILE NOT FOUND\n";
        exit(1);
    }

    string line;
    while (getline(fileStream, line)) {
        lines.push_back(line);
    }


    bool key1 = false;
    bool key2 = false;
    bool key3 = false;
    cout << "Here are the infos in the file provided" << endl;
    for (int i = 0; i < lines.size(); i++) {
        cout << lines[i] << endl;
        if (lines[i].find("[continents]") != string::npos) {
            key1 = true;
            continue;
        }
        if (lines[i].find("[countries]") != string::npos) {
            key1 = false;
            key2 = true;
            continue;
        }
        if (lines[i].find("[borders]") != string::npos) {
            key2 = false;
            key3 = true;
            continue;

        }

        //Debug helper
        //cout<<key1<<endl;
        //cout<<key2<<endl;  
        //cout<<key3<<endl;

        if (key1) {
            // converting the line into an array
            string arr[3];
            int l = 0;
            stringstream ssin(lines[i]);
            while (ssin.good() && l < 3) {
                ssin >> arr[l];
                ++l;
            }

            //cout<<arr[0]<<endl; debug helper

            if (arr[0].empty())
                cout << "Blank line" << endl;
            else {
                Continent* continent_pointer = new Continent(arr[0]);
                continents.push_back(continent_pointer);
                /*delete continent_pointer;
                continent_pointer=NULL;*/
            }
        }
        if (key2) {
            // converting the line into an array
            string arr[5];
            int l = 0;
            stringstream ssin(lines[i]);
            while (ssin.good() && l < 5) {
                ssin >> arr[l];
                ++l;
            }
            if (arr[0].empty())
                cout << "Blank line" << endl;
            else {
                int tID = stoi(arr[0]);
                string TName = arr[1];
                int continentID = stoi(arr[2]);
                Territory* t = new Territory(tID, TName);
                territories.push_back(t);
                (*continents[continentID - 1]).setTerritories(t);
                //pointers.push_back(t);
            }
        }

        if (key3) {

            //Transforming the line in a vector of string using stringstream
            stringstream ssin(lines[i]);
            vector<string> boarders_info((istream_iterator<string>(ssin)),
                istream_iterator<string>());


            for (int j = 1; j < boarders_info.size(); j++) {
                //cout<<boarders_info[j]<<endl; debug helper
                //territories[stoi(boarders_info[0])-1].setEdges(pointers[stoi(boarders_info[j])-1]);
                (*territories[stoi(boarders_info[0]) - 1]).setEdges((territories[stoi(boarders_info[j]) - 1]));
            }

        }
    }

    mainMap = new Map(nameWorld, territories, continents);

}

Map* MapLoader::returnMap() {
    return this->mainMap;
};
