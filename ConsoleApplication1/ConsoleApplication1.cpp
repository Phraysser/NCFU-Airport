#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

class Airport {
private:
	vector<Flight> flights;

public:
	bool compareTime(const string& time1, const string& time2, const string& time3) {
		stringstream ss1(time1);
		stringstream ss2(time2);
		stringstream ss3(time3);

		int hh1, mm1, hh2, mm2, hh3, mm3;
		char separator;

		ss1 >> hh1 >> separator >> mm1;
		ss2 >> hh2 >> separator >> mm2;
		ss3 >> hh3 >> separator >> mm3;

		if (hh1 <= hh2 <= hh3) {
			return true;
		}
		else {
			return false;
		}
	}
	bool compareDate(const string& minDate, const string& Date, const string& maxDate) {
		stringstream dd1(minDate);
		stringstream dd2(Date);
		stringstream dd3(maxDate);

		int hh1, mm1, kk1, hh2, mm2, kk2, hh3, mm3, kk3;
		char separator;

		dd1 >> hh1 >> separator >> mm1 >> separator >> kk1;
		dd2 >> hh2 >> separator >> mm2 >> separator >> kk2;
		dd3 >> hh3 >> separator >> mm3 >> separator >> kk3;
		if (kk2 < kk1 || kk2 > kk3) {
			return false;
		}
		else if (kk2 == kk1 && mm2 < mm1) {
			return false;
		}
		else if (kk2 == kk3 && mm2 > mm3) {
			return false;
		}
		else if (kk2 == kk1 && mm2 == mm1 && hh2 < hh1) {
			return false;
		}
		else if (kk2 == kk3 && mm2 == mm3 && hh2 > hh3) {
			return false;
		}
		return true;
	}
	void addFlight(string dest, string date, string time, int seats, string cls, double pr) {
		Flight newFlight(dest, date, time, seats, cls, pr);
		flights.push_back(newFlight);
	}
	void deleteFlight(string dest, string date, string time, int seats, string cls, double pr) {
		flights.pop_back();
	}
	void searchFlights(string dest, string minDate, string maxDate, string mintime,string maxtime, string cls, double minPrice, double maxPrice) {
		for (Flight flight : flights) {
			if (flight.destination == dest && compareDate(minDate,flight.departureDate, maxDate) && compareTime(mintime, flight.departureTime, maxtime)
				&& flight.seatClass == cls && (minPrice <= flight.price <= maxPrice) && flight.seatsAvailable > 0) {
				cout << "Полет в " << flight.destination << " на " << flight.departureDate << " в " << flight.departureTime
					<< " доступен в " << flight.seatClass << " классе за " << flight.price << " с " << flight.seatsAvailable << " свободными местами." << endl;
				break;
			}
			else {
				cout << "Полетов с данными параметрами нет" << endl;
				break;
			}
		}
	}

	friend ostream& operator<<(ostream& os, const Airport& airport) {
		for (Flight flight : airport.flights) {
			os << "Назначение: " << flight.destination << ", Дата: " << flight.departureDate << ", Время: " << flight.departureTime
				<< ", Свободных мест доступно: " << flight.seatsAvailable << ", Класс: " << flight.seatClass << ", Цена: " << flight.price << endl;
		}
		return os;
	}

	friend istream& operator>>(istream& is, Airport& airport) {
		string dest, date, time, cls;
		int seats;
		double pr;
		is >> dest >> date >> time >> seats >> cls >> pr;
		airport.addFlight(dest, date, time, seats, cls, pr);
		return is;
	}

	void saveToFile(string filename) {
		ofstream file(filename);
		if (file.is_open()) {
			for (Flight flight : flights) {
				file << flight.destination << " " << flight.departureDate << " " << flight.departureTime << " "
					<< flight.seatsAvailable << " " << flight.seatClass << " " << flight.price << endl;
			}
			file.close();
		}
		else {
			cout << "Невозможно открыть файл" << endl;
		}
	}

	void loadFromFile(string filename) {
		ifstream file(filename);
		if (file.is_open()) {
			string dest, date, time, cls;
			int seats;
			double pr;
			while (file >> dest >> date >> time >> seats >> cls >> pr) {
				addFlight(dest, date, time, seats, cls, pr);
			}
			file.close();
		}
		else {
			cout << "Невозможно открыть файл" << endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	int o;
	cout << "1. Добавление полета" << endl;
	cout << "2. Поиск полета" << endl;
	cout << "Введите номер функции: ";
	cin >> o;
	switch (o) {
	case 1:
	{
		Airport airport;
		string answer;
		string answer2;
		string destination;
		string departureDate;
		string departureTime;
		int seatsAvailable;
		string seatClass;
		double price;
		while (answer2 != "n") {
			cout << "Введите место назначения" << endl;
			cin >> destination;
			cout << "Введите дату назначения" << endl;
			cin >> departureDate;
			cout << "Введите время назначения" << endl;
			cin >> departureTime;
			cout << "Введите количество свободных мест" << endl;
			cin >> seatsAvailable;
			cout << "Введите тип класса" << endl;
			cin >> seatClass;
			cout << "Введите цену за билет" << endl;
			cin >> price;
			airport.addFlight(destination, departureDate, departureTime, seatsAvailable, seatClass, price);
			cout << airport;
			cout << "Сохранить полет в базу данных ? y/n ";
			cin >> answer;
			if (answer == "y" || answer == "Y") {
				airport.saveToFile("Flight.txt");
				cout << "Добавить еще 1 полет ? y/n ";
				cin >> answer2;
			}
			else {
				airport.deleteFlight(destination, departureDate, departureTime, seatsAvailable, seatClass, price);
				cout << "Добавить еще 1 полет ? y/n ";
				cin >> answer2;
			}
		}
		break;
	}
	case 2:
	{
		Airport airport;
		airport.loadFromFile("Flight.txt");
		string answer, dest, minDate, maxDate, minTime, maxTime, Class;
		double minPrice, price;
		cout << "Введите место назначения" << endl;
		cin >> dest;
		cout << "Введите минимальную дату назначения" << endl;
		cin >> minDate;
		cout << "Введите максимальную дату назначения" << endl;
		cin >> maxDate;
		cout << "Введите минимальное время назначения" << endl;
		cin >> minTime;
		cout << "Введите максимальное время назначения" << endl;
		cin >> maxTime;
		cout << "Введите тип класса" << endl;
		cin >> Class;
		cout << "Введите минимальную цену за билет" << endl;
		cin >> minPrice;
		cout << "Введите максимальную цену за билет" << endl;
		cin >> price;
		airport.searchFlights(dest, minDate, maxDate, minTime, maxTime, Class, minPrice, price);
		break;
	}
	}
	return 0;
}