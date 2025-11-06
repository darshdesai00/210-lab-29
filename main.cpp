// COMSC-210 | Lab 29 | Darsh Desai
// IDE used: VS Code
// Description: Stock Market Trends Simulation - (Pseudocode)

// Include your headers: 
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>
using namespace std;

// Func prototype
// void = no return value
// simulate_day = your function name
// (map<string, array<list<double>, 3>> &market, int day) = inputs
void simulate_day(map<string, array<list<double>, 3>> &market, int day);

int main() {
// Initialize a map to store company information
// Each key = company ticker (e.g., AAPL)
// Each value = array with 3 lists for [price, volume, sentiment]
map<string, array<list<double>, 3>> market;
    
// Open an external file to read initial stock data
ifstream fin("stocks_data.txt");
if (!fin) {
cerr << "Error: could not open stocks_data.txt" << endl;
return 1;
}

string ticker;
double price, volume, sentiment;

// Read data find file and populate the map
// For each line get the company name and data
// Add the price to the company’s price list
// Add the volume to the company’s volume list
// Add the sentiment to the company’s sentiment list
while (fin >> ticker >> price >> volume >> sentiment) {
market[ticker][0].push_back(price);
market[ticker][1].push_back(volume);
market[ticker][2].push_back(sentiment);
    }

// Close the file
fin.close();

// Display the initial state of the market
// For each company:
// Print ticker, latest price, volume, and sentiment
cout << "Initial Market State:\n";
for (auto &entry : market) {
cout << entry.first
<< " | Price: " << entry.second[0].back()
<< " | Volume: " << entry.second[1].back()
<< " | Sentiment: " << entry.second[2].back()
<< endl;
}

// outputs start of simulation
cout << "\n--- Begin Simulation ---\n" << endl;

// Below beginss the simulation loop
// For 25 time periods:
// Call the simulate_day() function each time step
for (int day = 1; day <= 25; day++) {
simulate_day(market, day);
}

// Display end message
cout << "\nSimulation complete after 25 time periods." << endl;

return 0;
}

// Define the simulate_day function
// This function simulates daily stock market changes
// For each company:
// Randomly choose whether to remove or update stock data
// If even day ---> remove last PRICE reading
// If odd day ---> remove last VOLUME reading
// Print which data was modified
// Print placeholder for adding/updating new stock data later
void simulate_day(map<string, array<list<double>, 3>> &market, int day) {
cout << "Time Period " << day << " Updates:\n";

for (auto &entry : market) {
bool didRemove = false;

// Even days remove price
if (day % 2 == 0) {
if (!entry.second[0].empty()) {
entry.second[0].pop_back();
cout << "  " << entry.first << ": removed last PRICE reading.\n";
didRemove = true;}
}
// Odd days remove volume
else {
if (!entry.second[1].empty()) {
entry.second[1].pop_back();
cout << "  " << entry.first << ": removed last VOLUME reading.\n";
didRemove = true;}
}

// If no data left to remove
if (!didRemove) {
cout << "  " << entry.first << ": nothing to remove (list empty).\n";
}

// Placeholder for later labs (Lab 30)
cout << "    [will be implemented later]\n";
}

cout << endl;
}