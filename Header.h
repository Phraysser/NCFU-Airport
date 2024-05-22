#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Struct.h"
using namespace std;
class Airport {
public:
	bool compareTime(const string&, const string&, const string&);
	bool compareDate(const string& , const string&, const string&);
	void addFlight(string, string, string, int, string, double);
	void deleteFlight(string, string, string, int, string, double);
	void searchFlights(string, string, string, string, string, string, double, double);
	friend ostream& operator<<(ostream&, const Airport&);
	friend istream& operator>>(istream&, Airport&);
	void saveToFile(string);
	void loadFromFile(string);
private:
	vector<Flight> flights;
};
