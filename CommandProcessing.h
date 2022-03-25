#ifndef CommandProcessing_h
#define CommandProcessing_h

#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

// class GameEngine;
class Command; //forward declaration for use in CommandProcessor
class CommandProcessor {
private:
    // readCommand: 
    // •gets commands from the console as a string,
    // •stores the command internally in a collection of Command objects using saveCommand()
    // •provides a public getCommand() to other objects such as the GameEngine or the Player
    void readCommand();
    void saveCommand(string s);

public:
    vector<Command> commandCollection;
    string commandStr;
    int currentState;
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
    CommandProcessor(); //default constructor
    CommandProcessor(const CommandProcessor& commandProcessorToCopy); //copy costructor
    friend ostream& operator << (ostream& outputStream, const CommandProcessor& c); //outstream overload
    void getCommand();
    // int getGameEngineState(GameEngine &ge1);
    bool validate(Command toValidate);
    ~CommandProcessor(); //destructor
};

class Command {
private:


public:
    void saveEffect(string s);
    string command;
    string effect;
    Command(); //default constructor
    Command(const Command& commandToCopy); //copy costructor
    friend ostream& operator << (ostream& outputStream, const Command& c); //outstream overload
    ~Command(); //destructor
};

class FileLineReader {
private:
    string readLineFromFile();

public:
    friend class FileCommandProcessorAdapter; //to allow access from FileCommandProcessorAdapter
    // fstream newfile;
    FileLineReader(); //default constructor
    FileLineReader(int, FileLineReader*);
    FileLineReader(const FileLineReader& input); //copy costructor
    friend ostream& operator << (ostream& outputStream, const FileLineReader& c); //outstream overload
    ~FileLineReader(); //destructor
};


// class FileLineReader;
class FileCommandProcessorAdapter : public CommandProcessor {
private:
    // readCommand: 
    // •gets commands from a file,
    // •stores the command internally in a collection of Command objects using saveCommand()
    // •provides a public getCommand() to other objects such as the GameEngine or the Player
    void readCommand();
    void saveCommand(string s);

public:
    vector<Command> commandCollection;
    string commandStr;
    int currentState;
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
     // FileLineReader* flr = new FileLineReader();
    FileLineReader flr;
    FileCommandProcessorAdapter(); //default constructor
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& commandProcessorToCopy); //copy costructor
    friend ostream& operator << (ostream& outputStream, const FileCommandProcessorAdapter& c); //outstream overload
    void getCommand();
    ~FileCommandProcessorAdapter(); //destructor
};



#endif

