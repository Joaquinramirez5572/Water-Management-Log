// Necessary directives
#include <iostream>
#include "WaterLog.h"
using namespace std;

int main() {
    WaterLog log; // Declares our water log object
    log.loadFromFile("data.txt"); // Load in our data

    int option = -1; // SO our first menu loop iteration can execute

    // Welcomes user
    cout << "Welcome to your very own personal water log application!" << endl << endl;
    cout << "\"Waste water today and face a dry tomorrow.\"" << endl;
    cout << "- Unknown" << endl << endl;

    // Our menu interface with each option calling a defined method
    while (option != 8) {
        cout << "Select from one of the menu options below!" << endl;
        cout << "1. Add entry" << endl;
        cout << "2. View entries" << endl;
        cout << "3. Set a new personalized water conservation goal" << endl;
        cout << "4. Provide usage statistics" << endl;
        cout << "5. Provide water management tips" << endl;
        cout << "6. Delete entry" << endl;
        cout << "7. Restart log" << endl;
        cout << "8. Exit" << endl << endl;
        // This allows us to validate the menu option when a non-integer is input
        while (!(cin >> option)) {
            cin.clear(); // Allows us to read new data
            cin.ignore(1000, '\n'); // Clears any bad data from the user from the buffer
            cout << endl << "Invalid input. Please enter a valid menu option: " << endl;
        }
        cout << endl;

        if (option == 1) {
            log.addEntry();
        }
        else if (option == 2) {
            log.displayEntries();
        }
        else if (option == 3) {
            log.makeGoal();
        }
        else if (option == 4) {
            log.printUsageStats();
        }
        else if (option == 5) {
            log.displayTips();
        }
        else if (option == 6) {
            log.deleteEntry();
        }
        else if (option == 7) {
            log.clearLog();
        }
        else if (option == 8) {
            break;
        }
        else {
            cout << endl << "The number you entered is not one of the menu options listed above. Please try again" << endl << endl;
        }
    }

    cout << "Thank you for using the water log system. Hope to see you tomorrow!" << endl; // Thanks the user

    return 0;
}