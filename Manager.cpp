#include "Manager.h"
using namespace std;

void Manager::readAirlines() {
    system("clear");
    cout << "Fetching data from files...\n";
    ifstream ifs("airlines.csv");
    if (ifs.is_open()) {
        string line;
        getline(ifs, line);
        while (getline(ifs, line)) {
            istringstream iss(line);
            string code, name, callsign, country;
            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, callsign, ',');
            getline(iss, country);
            AirLine airline(code, name, callsign, country);
            airlines.push_back(airline);
        }
    }
}

void Manager::readAirports() {
    ifstream ifs("airports.csv");
    if (ifs.is_open()) {
        string line;
        getline(ifs, line);
        while (getline(ifs, line)) {
            istringstream iss(line);
            string code, name, city, country, latitude, longitude;
            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, city, ',');
            getline(iss, country, ',');
            getline(iss, latitude, ',');
            getline(iss, longitude);
            Airport airport(code, name, city, country, stof(latitude), stof(longitude));
            airports.push_back(airport);
        }
    }
}

void Manager::readFlights() {
    ifstream ifs("flights.csv");
    if (ifs.is_open()) {
        string line;
        getline(ifs, line);
        while (getline(ifs, line)) {
            istringstream iss(line);
            string source, target, code;
            getline(iss, source, ',');
            getline(iss, target, ',');
            getline(iss, code);
            Airport from = searchAirport(source);
            Airport to = searchAirport(target);
            AirLine airline = searchAirline(code);
            if (airline.getCode() == "") throw invalid_argument("Flight has an invalid airline");
            Flight flight(from, to, airline);
            flights.push_back(flight);
        }
    }
}

AirLine Manager::searchAirline(string code) {
    for (auto it = airlines.begin(); it != airlines.end(); it++) {
        if (it -> getCode() == code) return *it;
    }
    return AirLine();
}

Airport Manager::searchAirport(string code) {
    for (auto it = airports.begin(); it != airports.end(); it++) {
        if (it -> getCode() == code) return *it;
    }
    return Airport();
}