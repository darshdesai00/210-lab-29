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
cerr << "Error: could not open file." << endl;
eturn 1;   
}
}

string ticker;
double price, volume, sentiment;

// Read data find file and populate the map
// For each line get the company name and data

