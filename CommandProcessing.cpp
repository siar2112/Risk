#include "CommandProcessing.h"
// #include "GameEngine.h"

using namespace std;

// GameEngine &ge1;


//********CommandProcessor**********
        //CommandProcessor has a collection of Commands
vector<Command> commandCollection;

CommandProcessor::CommandProcessor() {} //default constructor

void CommandProcessor::saveCommand(string s) {
    Command c;
    c.command = s; //assign command type from input
    c.saveEffect(s);
    this->commandCollection.push_back(c); //save the command to collection
};

void CommandProcessor::readCommand() {
    cout << "Please input a command." << endl;
    cin.ignore(); //needed to use cin in getline() after using "cin <<" previously
    getline(cin, commandStr); //to include whitespace in string
    cout << "commandStr is: " << commandStr << endl;
    saveCommand(commandStr);
};

void CommandProcessor::getCommand() {
    readCommand();
};

// int CommandProcessor::getGameEngineState(GameEngine &ge1){
//     // return ge1.state;
//     return ge1.state;
// };

bool CommandProcessor::validate(Command toValidate) {
    // cout << "GameEngine current state is: " << &ge1.state;
    return false;
};

//copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor& inputCP) {
    this->commandCollection = inputCP.commandCollection;
    this->commandStr = inputCP.commandStr;
    // cout << "\nCommandProcessor copied." << endl; //for debugging
};

//ostream overload
ostream& operator << (ostream& outputStream, const CommandProcessor& c) {
    outputStream << "CommandProcessor has: \ncommandCollection:" << endl;
    for (int i = 0; i < c.commandCollection.size(); i++) { //show commands
        outputStream << c.commandCollection.at(i) << endl;
    }
    outputStream << "commandStr: " << c.commandStr << endl;
    return outputStream;
};


//destructor
CommandProcessor::~CommandProcessor() {};


//********Command**********
Command::Command() {}  //default constructor

void Command::saveEffect(string s) {
    //assign effect corresponding to input
    if (regex_match(s, regex("(loadmap )(.*)"))) {
        this->effect = "Load map from file, transition to maploaded state.";
    }
    if (s == "validatemap") {
        this->effect = "Validate map, transition to mapvalidated state.";
    }
    if (regex_match(s, regex("(addplayer )(.*)"))) {
        this->effect = "Adds a player, transition to playersadded state.";
    }
    if (s == "gamestart") {
        this->effect = "Start game, transition to assignreinforcement state.";
    }
    if (s == "replay") {
        this->effect = "Restart new game, transition to start state.";
    }
    if (s == "quit") {
        this->effect = "Quit game, exit program.";
    }
    if (!(regex_match(s, regex("(loadmap )(.*)"))) && s != "validatemap" && !(regex_match(s, regex("(addplayer )(.*)"))) && s != "gamestart" && s != "replay" && s != "quit") {
        //case of invalid input should save a record of this in the effect variable
        this->effect = "Invalid command entered. No effect on game.";
    }
};


//copy constructor
Command::Command(const Command& inputCommand) {
    this->command = inputCommand.command;
    this->effect = inputCommand.effect;
    // cout << "\nCommand copied." << endl; //for debugging
};

//ostream overload
ostream& operator << (ostream& outputStream, const Command& c) {
    outputStream << "Command has: \ncommand:" << c.command << endl;
    outputStream << "effect: " << c.effect << endl;
    return outputStream;
};

//destructor
Command::~Command() {};


//***********FileCommandProcessorAdapter**************
        //default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter() :CommandProcessor() {
    // FileLineReader flr;
};

void FileCommandProcessorAdapter::readCommand() {
    // commandStr = (*flr).readLineFromFile();
    cout << "readCommand() used." << endl; //for debugging
    commandStr = flr.readLineFromFile();
    saveCommand(commandStr);
};

void FileCommandProcessorAdapter::saveCommand(string s) {
    cout << "saveCommand() used with " << s << endl; //for debugging
    Command c;
    c.command = s; //assign command type from input
    c.saveEffect(s);
    this->commandCollection.push_back(c); //save the command to collection
};

void FileCommandProcessorAdapter::getCommand() {
    readCommand();
};

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {}; //destructor

//************FileLineReader**************************
static int lineNumber = 0;
// fstream newfile;
FileLineReader::FileLineReader() { //default constructor
    cout << "FileLineReader created." << endl;
};

string FileLineReader::readLineFromFile() {
    cout << "Specify filename.txt" << endl;
    string filename = "/Users/liamj/Documents/345-Fall-2021/Cards-Folder/"; //specify your local directory here
    string temp;
    cin >> temp;
    filename += temp;
    fstream newfile;
    newfile.open(filename, ios::in); //open a file to perform read operation using file object.
                                                    //may need path/filename to work.
    cout << "Opening file: " << filename << endl;
    if (newfile.is_open()) {   //checking whether the file is open
        cout << "File is open." << endl;
        string tp;
        int iteration = 0;
        while (getline(newfile, tp)) {  //read data from file object and put it into string.
            if (lineNumber == iteration) { //will only return next unread line from file
                lineNumber++;
                return tp;   //print the data of the string
            }
            iteration++;
        }
        newfile.close();   //close the file object.
    }
    return "";
};

//copy constructor
FileLineReader::FileLineReader(const FileLineReader& input) {
    //no members
};

//ostream overload
ostream& operator << (ostream& outputStream, const FileLineReader& f) {
    outputStream << "FileLineReader ostream." << endl;
    return outputStream;
};

//destructor
FileLineReader::~FileLineReader() {};
