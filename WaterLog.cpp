// Necessary directives
#include "WaterLog.h"
#include <iostream>
#include <fstream> // Lets us read and write on the files
#include <iomanip> // For formatting
#include <sstream> // Lets us have strings as stream objects
#include <algorithm> // Helps us sort the date entries
using namespace std;

// Our constructor definition
WaterLog::WaterLog() {
    goal = "N/A"; // Sets it to "N/A" by default
}

// getValidInt() definition that validates any int-type of user input
int WaterLog::getValidInt(string prompt) {
    int value;
    cout << prompt; // Shows the specific prompt for a given value
    while (!(cin >> value) || value < 0) { // Catches any non-integers or negative values
        cin.clear(); // Lets us read again after a failed input
        cin.ignore(1000, '\n'); // Clears out the buffer bad data
        cout << "Invalid input. Please enter a positive number: ";
    }
    return value; // We return the valid value once we actually get a valid value
}

// entryExists() definition
bool WaterLog::entryExists(string date) {
    // Loops through every entry in the vector (log), and if the date is found, it returns true, otherwise, false
    for (int i = 0; i < entries.size(); i++) {
        if (entries[i].getDate() == date) {
            return true;
        }
    }
    return false;
}

// addEntry() definition
void WaterLog::addEntry() {
    // Necessary variables
    string date;
    int showerMin, laundryLoads, dishCycles, faucetMin;

    // We are just prompting the user for a date and their usage info. Note: For usage info, we validate each variable to make sure it is of type int
    cout << "Enter the date (e.g. 4/9): ";
    cin >> date;

    // Checks if the date is already there
    if (entryExists(date)) {
        cout << "An entry for this date already exists." << endl << endl;
        return;
    }

    int month = stoi(date.substr(0, date.find('/'))); // We extract the month by locating everything before the slash and we convert it into an integer (with the "stoi")

    showerMin = getValidInt("Enter shower minutes: ");
    laundryLoads = getValidInt("Enter laundry loads: ");
    dishCycles = getValidInt("Enter dishwasher cycles: ");
    faucetMin = getValidInt("Enter faucet minutes: ");

    cout << endl;

    entries.push_back(WaterEntry(date, month, showerMin, laundryLoads, dishCycles, faucetMin)); // Adds the entry to the vector!
    saveToFile("data.txt"); // Saves the entry to the file

    // This is a lambda sorting algorithm that sorts each entry after the new entry is added. I used this sorting algorithm because we are accessing variables from the outer scope
    sort(entries.begin(), entries.end(), [](WaterEntry a, WaterEntry b) { // The "[](WaterEntry a, WaterEntry b" basically just lets us capture the variables right where we need them and compares them to decide which comes first, receiving them by VALUE
        int dayA = stoi(a.getDate().substr(a.getDate().find('/') + 1)); // Extracts the first day and converts it to an integer
        int dayB = stoi(b.getDate().substr(b.getDate().find('/') + 1)); // Extracts the second day and converts it to an integer

        // If the entries are in different months, the one with the smaller month goes first
        if (a.getMonth() != b.getMonth()) {
            return a.getMonth() < b.getMonth();
        }
        return dayA < dayB;
        }); // Closes the sort/lambda function

    cout << "Done! Your data entry has been added to the log." << endl << endl;
}

// deleteEntry() definition
void WaterLog::deleteEntry() {
    // Asks user for date
    string date;
    cout << "Enter the date of the entry to delete (e.g. 4/9): ";
    cin >> date;
    cout << endl;

    // If the date exitst, loop through the vector (log) and removes it at the specified index
    if (entryExists(date)) {
        for (int i = 0; i < entries.size(); i++) {
            if (entries[i].getDate() == date) {
                entries.erase(entries.begin() + i); // Gives the EXACT position of the element to remove
                break;
            }
        }
        saveToFile("data.txt"); // Saves it to the file
        cout << "The data entry for " << date << " has been removed from the log." << endl << endl;
    }
    else {
        cout << "Sorry, no entry was found." << endl << endl; // Outputs when we can't find the entry
    }
}

// displayEntries() definition
void WaterLog::displayEntries() {
    cout << setw(44) << "Water Log" << endl; // Allows us to center the log title
    cout << "Goal: " << goal << endl << endl; // Shows the user their goal

    string monthNames[] = { "", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" }; // An array that allows us to have a subtitle for the given month's entries

    // We iterate through all 12 months. For each month, we do a quick check to see if any entries belong to it, and if it does not, continue (so we don't get empty months in the output)
    for (int m = 1; m <= 12; m++) {
        bool hasEntries = false;
        for (int i = 0; i < entries.size(); i++) {
            if (entries[i].getMonth() == m) {
                hasEntries = true;
                break;
            }
        }
        if (!hasEntries) continue; // Makes sure we don't get any empty months

        // Prints the month name header and alligns them, with a seperator line
        cout << "------------------------------------ " << monthNames[m] << " ------------------------------------" << endl;
        cout << left << setw(10) << "Date" << setw(10) << "Shower" << setw(10) << "Laundry" << setw(13) << "Dishwasher" << setw(10) << "Faucet" << setw(10) << "Total (gallons)" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        // This inner loop skips any entries not belonging to the current month, and we apply the formulas to accumalate the result into monthTotal for the gaol check below
        double monthTotal = 0;
        for (int i = 0; i < entries.size(); i++) {
            if (entries[i].getMonth() != m) {
                continue;
            }
            // Gets the total for that specific entry
            WaterEntry e = entries[i];
            monthTotal += e.getTotal();
            // Formulas
            int laundryMin = e.getLaundryLoads() * 45;
            int dishMin = e.getDishwasherCycles() * 65;
            cout << left << setw(10) << e.getDate() << setw(10) << e.getShowerMinutes() << setw(10) << laundryMin << setw(13) << dishMin << setw(10) << e.getFaucetMinutes() << fixed << setprecision(0) << e.getTotal() << endl; // Prints each entry's row
        }

        cout << endl; // Formatting

        if (goal != "N/A") { // Checks if a goal is set
            int goalVal = 0; // Default goal value
            stringstream ss(goal.substr(goal.find("under ") + 6)); // If it is, we grab the number as a stream string 
            ss >> goalVal; // Extracts the numerical value and the next line compares it to the monthTotal for bookkeeping
            if (monthTotal > goalVal) {
                cout << "Warning: You are currently exceeding your goal for this month!" << endl;
            }
        }
    }
    cout << endl;
}

// saveToFile() definition. I added this for 3B for convinience since we are saving a lot of the time
void WaterLog::saveToFile(string filename) {
    // Opens our text file to write on it (overwriting whatever what was originally in the file) and writes the goal with the specified format
    ofstream outFile(filename);
    outFile << "GOAL:" << goal << endl;
    // Loops through every entry and writes it as a single spaced line (note: I mentioned this in 3B SDD, but the month is stored explicitly as a seperate field so it can be reconstructed with the constructor)
    for (int i = 0; i < entries.size(); i++) {
        WaterEntry e = entries[i];
        outFile << e.getDate() << " " << e.getMonth() << " " << e.getShowerMinutes() << " " << e.getLaundryLoads() << " " << e.getDishwasherCycles() << " " << e.getFaucetMinutes() << endl; // Writes it onto the file!
    }
    outFile.close(); // Closes the file for good practice
}

// loadFromFile() definition. I added this for 3B for convinience since we are reading a lot of the time
void WaterLog::loadFromFile(string filename) {
    // Attempts to open the text file, and if it doesn't exist, it returns false
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }

    entries.clear(); // Clears any existing entries beforehand (so we can prevent any duplicates)
    string line;

    // Reads the file line by line
    while (getline(inFile, line)) {
        if (line.substr(0, 5) == "GOAL:") { // Reads everything after "GOAL:" as the goal string and skips to the next line
            goal = line.substr(5);
            continue;
        }

        // Basically skips any empty lines
        if (line.empty()) {
            continue;
        }

        // We parse space-seperated values as stream objects to their own respective fields
        stringstream ss(line);
        string date;
        int month, showerMin, laundryLoads, dishCycles, faucetMin;
        ss >> date >> month >> showerMin >> laundryLoads >> dishCycles >> faucetMin;
        entries.push_back(WaterEntry(date, month, showerMin, laundryLoads, dishCycles, faucetMin)); // We make a new WaterEntry and push those onto the vector
    }
    inFile.close(); // Closes the file for good bookkeeping
}

// printUsageStats() definition
void WaterLog::printUsageStats() {
    string mode; // The mode in which they want to read it
    cout << "View statistics by Month or Total (Month/Total): ";
    cin >> mode;
    cout << endl;

    // Executes if user asks by MONTH
    if (mode == "Month") {
        int month;
        month = getValidInt("Enter the month number (e.g. 4 for April): "); // Validates the month
        cout << endl;

        // Default values
        double showerTotal = 0, laundryTotal = 0, dishTotal = 0, faucetTotal = 0, grandTotal = 0;
        int count = 0; // Keeps track of how many entries there are in that month
        
        // Filters entries by the requested month and accumalates all of the gallons for each activity
        for (int i = 0; i < entries.size(); i++) {
            if (entries[i].getMonth() == month) {
                showerTotal += entries[i].getShowerMinutes() * 2.0;
                laundryTotal += entries[i].getLaundryLoads() * 40.0;
                dishTotal += entries[i].getDishwasherCycles() * 6.0;
                faucetTotal += entries[i].getFaucetMinutes() * 2.2;
                grandTotal += entries[i].getTotal();
                count++;
            }
        }

        // Executes when there's no entries for that month
        if (count == 0) {
            cout << "No entries found for that month." << endl << endl;
            return;
        }

        // We compare each activity by gallons by making "showering" the most used activity first and doing an activity-by-activity comparison
        string mostUsed = "showering";
        double mostVal = showerTotal;

        // The activity replaces "mostUsed" if it is most used and "mostVal" if it has the most gallons
        if (laundryTotal > mostVal) { 
            mostUsed = "from doing laundry";
            mostVal = laundryTotal; 
        }
        if (dishTotal > mostVal) { 
            mostUsed = "dishwashing"; 
            mostVal = dishTotal; 
        }
        if (faucetTotal > mostVal) { 
            mostUsed = "from your faucet"; 
            mostVal = faucetTotal; 
        }

        // Our month array and selects the correct name based on the month number. The ternary operator acts as a safety net if an out-of-range  number slips through, acting as "that month"
        string monthNames[] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
        string mName = (month >= 1 && month <= 12) ? monthNames[month] : "that month";

        cout << "Press C to continue to each statistic." << endl << endl;

        // STAT 1
        cout << "* The activity that used the most water in " << mName << " is " << mostUsed << "." << endl;
        string cont; // Executes when they enter "C"
        cin >> cont;

        // STAT 2: total gallons and and whether the user is on track with their goal. Goal value is extracted in the same way as it is in our displayEntries() method
        double cost = (grandTotal * 0.01) + 30.0;
        bool onTrack = true; // Automatically set to true so no "on-track" message prints when no goal is set
        if (goal != "N/A") {
            int goalVal = 0;
            // Same process as in displayEntries()
            stringstream ss(goal.substr(goal.find("under ") + 6));
            ss >> goalVal;
            onTrack = grandTotal <= goalVal; // Explicitly tells us what on track means
        }

        // Continuation of stat 2 where it shows how many gallons of water the user has used so far with the month
        cout << "* You have used " << fixed << setprecision(0) << grandTotal << " gallons of water so far in " << mName << ". ";
        if (goal != "N/A") {
            // Tells the user if they are on track or not
            if (onTrack) {
                cout << "Congratulations, you are on track so far with your goal!";
            }
            else {
                cout << "You are currently exceeding your goal!";
            }
        }

        cout << endl;
        cin >> cont;

        // STAT 3: Tells the user how much the cost is for that month
        cout << "* The total cost for that much water is about $" << fixed << setprecision(2) << cost << " a month" << endl;
        cin >> cont;

        // STAT 4: Gives the percentage difference from the 10k gallin american average using the standard percent difference formula
        double avgAmerican = 10000.0;
        double percentDiff = abs(grandTotal - avgAmerican) / ((grandTotal + avgAmerican) / 2.0) * 100.0;
        cout << "* The percent difference between your water household usage and the average American water household usage is approximately a " << fixed << setprecision(0) << percentDiff << "% difference." << endl << endl;

    }

    // Executes for TOTAL (by extension, 3 different stats)
    else {
        double showerTotal = 0, laundryTotal = 0, dishTotal = 0, faucetTotal = 0, grandTotal = 0;

        // This total segment does the same accumulation as the monthly path but with no month filter!
        for (int i = 0; i < entries.size(); i++) {
            showerTotal += entries[i].getShowerMinutes() * 2.0;
            laundryTotal += entries[i].getLaundryLoads() * 40.0;
            dishTotal += entries[i].getDishwasherCycles() * 6.0;
            faucetTotal += entries[i].getFaucetMinutes() * 2.2;
            grandTotal += entries[i].getTotal();
        }

        // Same logic as the month comparison values
        string mostUsed = "showering";
        double mostVal = showerTotal;

        if (laundryTotal > mostVal) { 
            mostUsed = "from doing laundry";
            mostVal = laundryTotal;
        }
        if (dishTotal > mostVal) { 
            mostUsed = "dishwashing"; 
            mostVal = dishTotal; 
        }
        if (faucetTotal > mostVal) { 
            mostUsed = "from your faucet";
            mostVal = faucetTotal;
        }

        cout << "Press C to continue to each statistic." << endl << endl;

        // STAT 1: Most used activity of all time!
        cout << "* Your most used activity is " << mostUsed << "." << endl;
        string cont;
        cin >> cont;

        // STAT 2: How many gallons of water the user used so far.
        cout << "* You have used " << fixed << setprecision(0) << grandTotal << " gallons of water so far." << endl;
        cin >> cont;

        // STAT 3: Instead of comparing it to the average American household, we compare it to an olympic-sized swimming pool just for fun
        double poolGallons = 660000.0;
        double percent = (grandTotal / poolGallons) * 100.0;
        cout << "* That many gallons is about " << fixed << setprecision(6) << percent << "% of an Olympic-sized swimming pool!" << endl << endl;
    }
}

// makeGoal() definition
void WaterLog::makeGoal() {
    int people;
    people = getValidInt("Enter the number of people in your household: "); // Validates the number of people in the house
    cout << endl;

    // Produces a goal (and we actually use the EPA formula for this) that the user should stay under
    int goalGallons = people * 300;
    goal = "Try to stay under " + to_string(goalGallons) + " gallons a month!"; // Makes the goalGallons a string
    cout << "Based on your input data, the number of gallons you should not exceed in a month for a " << people << "-person household (from U.S. EPA) is " << goalGallons << " gallons." << endl << endl;
    saveToFile("data.txt"); // Saves it to the file
}

// displayTips() definition
void WaterLog::displayTips() {
    // Self-explanatory; we just produce some basic water management tips
    cout << "1. Colder water cycles strain the water supply less" << endl;
    cout << "2. Installing low-flow shower heads and faucet aerators can help limit water usage" << endl;
    cout << "3. Dishwashers are more water-friendly than handwashing" << endl;
    cout << "4. Insulating pipes reduces the time waiting for hot water" << endl;
    cout << "5. Target shower time should be limited to 5-10 minutes!" << endl << endl;
}

// clearLog() definition
void WaterLog::clearLog() {
    string confirm; // Confirmation of clearing the log
    cout << "Are you sure you want to clear the log? (Yes/No): ";
    cin >> confirm;
    cout << endl;

    // If the user does want to clear it, clear it!
    if (confirm == "Yes") {
        entries.clear();
        goal = "N/A";
        saveToFile("data.txt");
        cout << "Done. The log has been cleared." << endl << endl;

    }
    // Otherwise, say got it. We don't want them clearing it on accident, so this acts as a safety net confirmation for them
    else {
        cout << "Got it." << endl << endl;
    }
}