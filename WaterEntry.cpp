#include "WaterEntry.h" // Necessary directive

// Constructor definition
WaterEntry::WaterEntry(string date, int month, int showerMins, int laundryLoads, int dishwasherCycles, int faucetMinutes) {
    // Allows us to access member variables
    this->date = date;
    this->month = month;
    this->showerMinutes = showerMins;
    this->laundryLoads = laundryLoads;
    this->dishwasherCycles = dishwasherCycles;
    this->faucetMinutes = faucetMinutes;
}

// calculateTotal() definition (note: all of our formulas listed here are already explicitly stated and outlined in the SDD)
double WaterEntry::calculateTotal() {
    double shower = showerMinutes * 2.0;
    double laundry = laundryLoads * 40.0;
    double dishwasher = dishwasherCycles * 6.0;
    double faucet = faucetMinutes * 2.2;
    return shower + laundry + dishwasher + faucet;
}

// getTotal() definition
double WaterEntry::getTotal() {
    return calculateTotal();
}

// getMonth() definition
int WaterEntry::getMonth() {
    return month;
}

// getDate() definition
string WaterEntry::getDate() {
    return date;
}

// getShowerMinutes() definition
int WaterEntry::getShowerMinutes() {
    return showerMinutes;
}

// getLaundryLoads() definition
int WaterEntry::getLaundryLoads() {
    return laundryLoads;
}

// getDishwasherCycles() definition
int WaterEntry::getDishwasherCycles() {
    return dishwasherCycles;
}

// getFaucetMinutes() definition
int WaterEntry::getFaucetMinutes() {
    return faucetMinutes;
}