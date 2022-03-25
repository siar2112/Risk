#ifndef Cards_h
#define Cards_h

#pragma once
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
// #include "Orders.h"
// #include "Player.h"

using namespace std;


class Card {
public:
    // int* ptr;
    static int typeNumber;
    string typeOfCard;
    Card(); //default constructor
    Card(int, Card*);
    Card(const Card& inputCard); //copy costructor
    friend ostream& operator << (ostream& outputStream, const Card& c); //outstream overload
    // void play(Player p, Deck d); //adds order from this Card to Player's OrdersList, removes Card from Player's Hand and returns card to deck
    ~Card(); //destructor
};

class Deck {
public:
    int randomCardNumber;
    int numCardsInDeck;
    Deck();
    Deck(const Deck& inputDeck); // copy constructor
    friend ostream& operator << (ostream& outputStream, const Deck& d); //outstream overload
    vector<Card> deckOfCards;
    Card draw();
    ~Deck(); //destructor
};

class Hand {
public:
    Hand();
    Hand(const Hand& inputHand); // copy constructor
    void addCardToHand(Card toAdd);
    void removeCardFromHand(Card toRemove);
    vector<Card> handOfCards;
    friend ostream& operator << (ostream& outputStream, const Hand& h); //outstream overload
    ~Hand(); //destructor
};

#endif
#pragma once

