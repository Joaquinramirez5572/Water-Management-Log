// Necessary guards and directives
#ifndef WATERENTRY_H
#define WATERENTRY_H
#include <string>
using namespace std;

// Class definition
class WaterEntry {
private:
    // Private attributes outlined in the class diagram
    string date;
    int month;
    int showerMinutes;
    int laundryLoads;
    int dishwasherCycles;
    int faucetMinutes;

public:
    // Public methods outlined in the class diagram
    WaterEntry(string date, int month, int showerMins, int laundryLoads, int dishwasherCycles, int faucetMinutes);
    double calculateTotal();
    double getTotal();
    int getMonth();
    string getDate();
    int getShowerMinutes();
    int getLaundryLoads();
    int getDishwasherCycles();
    int getFaucetMinutes();
};

#endif // End guard