#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
struct Flight {
	string destination;
	string departureDate;
	string departureTime;
	int seatsAvailable;
	string seatClass;
	double price;

	Flight(string dest, string date, string time, int seats, string cls, double pr) {
		destination = dest;
		departureDate = date;
		departureTime = time;
		seatsAvailable = seats;
		seatClass = cls;
		price = pr;
	}
};