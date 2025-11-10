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

// Function prototype
void simulate_day(map<string, array<list<double>, 3>> &market, int day);

int main() {
srand(time(0)); // Initialize random seed 

// Initialize a map to store company information
// Each value = array with 3 lists for [price, volume, sentiment]
map<string, array<list<double>, 3>> market;

// Read starting data from file
ifstream fin("stocks_data.txt");
if (!fin) {
cerr << "Error: could not open stocks_data.txt" << endl;
return 1;
}

string ticker;
double price, volume, sentiment;

// Read data find file and populate the map
while (fin >> ticker >> price >> volume >> sentiment) {
market[ticker][0].push_back(price);
market[ticker][1].push_back(volume);
market[ticker][2].push_back(sentiment);
}

// Close the file
fin.close();

// Display the initial state of the market
cout << "==============================\n";
cout << "Initial Market State:\n";
cout << "==============================\n";

// Print ticker, latest price, volume, and sentiment
for (auto &entry : market) {
cout << setw(6) << left << entry.first
<< " | Price: $" << fixed << setprecision(2) << entry.second[0].back()
<< " | Volume: " << entry.second[1].back()
<< " | Sentiment: " << entry.second[2].back() << endl;
}

// Outputs the start of simulation
cout << "\n--- Begin Simulation (Beta Phase) ---\n" << endl;

// Simulate 25 trading days
for (int day = 1; day <= 25; day++) {
simulate_day(market, day);
}

// Display end message
cout << "\nSimulation complete after 25 time periods." << endl;
return 0;
}

// Runs one simulated day of trading
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

cout << " Companies tracked today:\n";
for (auto &entry : market) {
double changePercent = (rand() % 401 - 200) / 10000.0; // Added a random daily change

if (!entry.second[0].empty()) {
double lastPrice = entry.second[0].back();
double newPrice = lastPrice * (1 + changePercent);
entry.second[0].push_back(newPrice); // stores the updated price
}

if (!entry.second[2].empty()) {
double lastSentiment = entry.second[2].back();
// Random daily sentiment change
double sentimentChange = (rand() % 21 - 10) / 10.0; // ±1.0 range
double newSentiment = lastSentiment + sentimentChange; // Between 0 and 100
// 0 - 100
if (newSentiment > 100) newSentiment = 100;
if (newSentiment < 0) newSentiment = 0;
entry.second[2].push_back(newSentiment);
}

cout << left << setw(8) << entry.first
<< "$" << setw(11) << fixed << setprecision(2) << entry.second[0].back()
<< setw(10) << fixed << setprecision(1) << entry.second[2].back()
<< endl;

// Track running total and count for average calculation
marketTotal += entry.second[0].back();
marketCount++;
}

// Compute and display the average market price across all companies in the data
double marketAverage = (marketCount > 0) ? marketTotal / marketCount : 0;

// Outputs messages
cout << "------------------------------------" << endl;
cout << "Average Price: $" << fixed << setprecision(2) << marketAverage << endl;
cout << "Companies Tracked: " << marketCount << endl;
cout << "Market Trend: Stable for now" << endl;
cout << endl;
}
