#include "Manager.h"
#include "Flight.cpp"
#include "Airport.cpp"
#include "AirLine.cpp"
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
            AirLine airline = searchAirline(code);
            if (airline.getCode().empty()) throw invalid_argument("Flight has an invalid attribute");
            Flight flight(source, target, airline);
            for (auto &airport : airports) {
                if (airport.getCode() == source){
                    airport.addFlight(flight);
                    break;
                }
            }
        }
    }
}

AirLine Manager::searchAirline(string code) {
    for (auto &airline : airlines) {
        if (airline.getCode() == code) return airline;
    }
    return {};
}
Airport Manager::searchAirport(std::string code) {
    for (auto &airport : airports) {
        if (airport.getCode() == code) return airport;
    }
    return {};
}

void Manager::fetchingmenu() {
    system("clear");
    std::cout << "\n\n\tFectching Data\n ";
}
void Manager::mainmenu() {
    system("clear");
    std::cout << "\tMain Menu\n\n";
    vector<std::string> options{"1. Browse Flights;","2. Browse Airports;","0. Exit!"};
    for (std::string s : options){
        std::cout << s << ";\n";
    }
    unsigned option;
    std::cout<<"Select an option: ";
    std::cin>>option;
    switch (option) {
        case 0:
            break;
        case 1:
            flightsmenu();
            break;
        case 2:
            airportsmenu();
            break;
    }

}

void Manager::flightsmenu() {
    system("clear");
    std::cout << "\tFlights Menu\n\n";
    vector<std::string> options{"1. Browse Flights by airport;","2. Browse Flights by City;","3. Browse Flights by coordinates;","4. Browse Flights by Airlines;","0. Go Back!"};
    for (std::string s : options){
        std::cout << s << ";\n";
    }
    unsigned option;
    std::cout<<"Select an option: ";
    std::cin>>option;
    switch (option) {
        case 0:
            break;
        case 1:
            //flightsairportmenu();
            break;
        case 2:
            //flightscitymenu();
            break;
        case 3:
            //flightscoordinatesmenu();
            break;
        case 4:
            //flightsairlinesmenu();
            break;
    }
}

void Manager::airportsmenu() {
    system("clear");
    std::cout << "\tAirports Menu\n\n";
    std::cout << "Airport code: ";
    std::string code;
    std::cin >> code;
    Airport ap=searchAirport(code);

    system("clear");
    std::cout << "\tAirports Menu\n\n";
    vector<std::string> options{"0. Go Back!"};
    for (std::string s : options){
        std::cout << s << ";\n";
    }
    unsigned option;
    std::cout<<"Select an option: ";
    std::cin>>option;
}
