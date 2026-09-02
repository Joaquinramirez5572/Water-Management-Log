// Necessary guards and directives
#ifndef WATERLOG_H
#define WATERLOG_H
#include <vector>
#include <string>
#include "WaterEntry.h"
using namespace std;

// Class definition
class WaterLog {
// Our private members and helpers in the class diagram
private:
    vector<WaterEntry> entries; // Our vector of water entries named "entries"
    string goal;
    bool entryExists(string date);
    int getValidInt(string prompt); // Allows us to validate any integer inputs


/*
These are our public member attributes outlined in the class diagram.
These public methods define a controlled interface for interacting with the log (add, delete, view, etc.; all of this is basically encapsulation)  while also hiding how the data is stored and managed internally, which is what makes it an ADT.
*/
public:
    WaterLog(); // This is what holds all of our water entries and what we use for MO2
    void addEntry();
    void deleteEntry();
    void displayEntries();
    void saveToFile(string filename); // Helps us save data, ensuring persistence
    void loadFromFile(string filename); // Helps us load our data for each program execution
    void printUsageStats();
    void makeGoal();
    void displayTips();
    void clearLog();
};

#endif // End guard