// COMSC-210 | Lab 31 | Darsh Desai
// IDE used: VS Code
// Description: Stock Market Trends Simulation - (Beta Release)

// Include your headers: 
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <cstdlib>
#include <iomanip>   
#include <cstdlib>   
#include <ctime> // For timestamps
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
cout << "==============================\n";
cout << "Initial Market State:\n";
cout << "==============================\n";
for (auto &entry : market) {
cout << entry.first
<< setw(6) << left << entry.first
<< " | Price: $" << fixed << setprecision(2) << entry.second[0].back()
<< " | Volume: " << entry.second[1].back()
<< " | Sentiment: " << entry.second[2].back() << endl;
    
}

// outputs start of simulation
cout << "\n--- Begin Simulation (Beta Phase) ---\n" << endl;

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
cout << "==============================" << endl;
cout << " Day " << day << " Summary:\n";

// Added in timestamps for each simulated day
time_t now = time(0);
cout << "Date: " << ctime(&now);
cout << "==============================\n";

cout << left << setw(8) << "Ticker" 
<< setw(12) << "Price ($)" 
<< setw(12) << "Sentiment" << endl;
cout << "------------------------------------" << endl;

double marketTotal = 0;
int marketCount = 0;

cout << "  Companies tracked today:\n";
for (auto &entry : market) {
double changePercent = (rand() % 401 - 200) / 10000.0; // Added a random daily change

if (!entry.second[0].empty()) {
double lastPrice = entry.second[0].back();
double newPrice = lastPrice * (1 + changePercent);
entry.second[0].push_back(newPrice); // stores the updated price
}

if (!entry.second[2].empty()) {
double lastSentiment = entry.second[2].back();
// Random daily sentiment change between -5 and +5 points
double sentimentChange = (rand() % 11 - 5);
double newSentiment = lastSentiment + sentimentChange;

 // Between 0 and 100
 if (newSentiment > 100) newSentiment = 100;
// where we left off .....


cout << left << setw(8) << entry.first
<< "$" << setw(11) << fixed << setprecision(2) << entry.second[0].back()
<< setw(10) << entry.second[2].back()
<< endl;

// Track running total and count for average calculation           
marketTotal += entry.second[0].back();
marketCount++;
}

// Compute and display the average market price across all companies in the data
double marketAverage = (marketCount > 0) ? marketTotal / marketCount : 0;

cout << "------------------------------------" << endl;
cout << "Average Price: $" << fixed << setprecision(2) << marketAverage << endl;
cout << "Companies Tracked: " << marketCount << endl;
cout << "Market Trend: Stable for now" << endl;
cout << endl;

}
