#include "Manager.h"
#include "Flight.cpp"
#include "Airport.cpp"
#include "AirLine.cpp"
#include "Network.cpp"
#include <unordered_set>
using namespace std;

void removeWhitespace(string& str) {
    auto it = find_if(str.begin(), str.end(), [](char c) {
        return isspace(c);
    });
    while (it != str.end()) {
        it = str.erase(it);
        it = find_if(it, str.end(), [](char c) {
            return isspace(c);
        });
    }
}

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
            removeWhitespace(name);
            removeWhitespace(country);
            AirLine airline(code, name, callsign, country);
            airlines.emplace(code, airline);
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
            removeWhitespace(name);
            removeWhitespace(city);
            removeWhitespace(country);
            Airport airport(code, name, city, country, stof(latitude), stof(longitude));
            airports.emplace(code, airport);
            network.addNode(airport);
        }
    }
}


void Manager::readFlights() {
    ifstream ifs("flights.csv");
    if (ifs.is_open()) {
        string line;
        while (getline(ifs, line)) {
            istringstream iss(line);
            string source, target, code;
            getline(iss, source, ',');
            getline(iss, target, ',');
            getline(iss, code);
            removeWhitespace(source);
            removeWhitespace(target);
            Flight flight(airports[source], airports[target], airlines[code]);
            network.addFlight(flight);
        }
    }
}

bool Manager::isInRange(double lat, double lon, Airport &ap, double range) {
    double lat1=lat;
    double lon1=lon;
    double lat2=ap.getLatitude();
    double lon2=ap.getLongitude();

    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return ( (rad * c) <= range );
}


void Manager::mainMenu() {
    system("clear");
    cout << "\tMain Menu\n\n";
    vector<string> options{ "1. Browse Flights",
                            "2. Browse Airports",
                            "3. Browse Airlines",
                            "0. Exit" };
    for (string s : options){
        cout << s << "\n";
    }
    unsigned option;
    cout << "Select an option: ";
    cin >> option;
    switch (option) {
        case 0:
            break;
        case 1:
            flightsMenu();
            break;
        case 2:
            airportsMenu();
            break;
        case 3:
            airlinesMenu();
            break;
        default:
            system("clear");
            cout << "ERROR: Invalid option\n(Press any key + ENTER to continue)\n";
            string s;
            cin >> s;
            mainMenu();
    }
}

void Manager::flightsMenu() {
    system("clear");
    cout << "\tFlights Menu\n\n";
    vector<string> options{"1. Browse Flights by airport",
                           "2. Browse Flights by City",
                           "3. Browse Flights by coordinates",
                           "4. Browse Flights by Airlines",
                           "0. Go Back!"};
    for (string s : options){
        cout << s << "\n";
    }
    unsigned option;
    cout << "Select an option: ";
    cin >> option;
    switch (option) {
        case 0:
            mainMenu();
            break;
        case 1:
            flightsAirportMenu();
            break;
        case 2:
            flightsCityMenu();
            break;
        case 3:
            flightsCoordinatesMenu();
            break;
        case 4:
            //flightsairlinesmenu();
            break;
        default:
            system("clear");
            cout << "ERROR: Invalid option\n(Press any key + ENTER to continue)\n";
            string s;
            cin >> s;
            flightsMenu();
    }
}

void Manager::airportsMenu() {
    system("clear");
    cout << "\tAirports Menu\n\n";
    vector<string> options{"1. Browse Airports per city",
                           "2. Browse Airports per country",
                           "3. Detailed info about an airport",
                           "0. Go Back!"};
    for (string s : options){
        cout << s << "\n";
    }
    unsigned option;
    cout << "Select an option: ";
    cin >> option;
    switch (option) {
        case 0:
            mainMenu();
            break;
        case 1:
            airportsCityMenu();
            break;
        case 2:
            airportsCountryMenu();
            break;
        case 3:
            searchForAirport();
            break;
        default:
            system("clear");
            cout << "ERROR: Invalid option\n(Press any key + ENTER to continue)\n";
            string s;
            cin >> s;
            airportsMenu();
    }
}

void Manager::airportsCityMenu() {
    string city;
    int n = 0;
    system("clear");
    cout << "\t Airports by City Menu\n\n";
    cout << "(Write the city in camel case, for example: NewYork)\n\n";
    cout << "Enter a city: ";
    cin >> city;
    for (auto node: network.getNodes()) {
        if (city == node.source.getCity()) {
            node.source.shortPrint();
            n++;
        }
    }
    if (n > 0)
        cout << "\nNumber of airports in " << city << ": " << n << endl;
    else
        cout << "\nNo airports found in this city\n";
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    airportsMenu();
}

void Manager::airportsCountryMenu() {
    string country;
    int n = 0;
    system("clear");
    cout << "\tAirports by Country Menu\n\n";
    cout << "(Write the countries in camel case, for example: UnitedStates)\n\n";
    cout << "Enter a country: ";
    cin >> country;
    for (auto node:network.getNodes()) {
        if (country == node.source.getCountry()) {
            cout << node.source.getCity() << ", ";
            node.source.shortPrint();
            n++;
        }
    }
    if (n > 0)
        cout << "\nNumber of airports in " << country << ": " << n << endl;
    else
        cout << "No airports found in this country\n";
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    airportsMenu();
}

void Manager::searchForAirport() {
    string airport;
    system("clear");
    cout << "Airport code: ";
    cin >> airport;
    for (auto node: network.getNodes()) {
        if (airport == node.source.getCode()) {
            cout << "Location: " << node.source.getCountry() << ", " << node.source.getCity() << endl;
            cout << "Coordinates: " << node.source.getLatitude() << " " << node.source.getLongitude() << "\n";
            cout << node.source.getName() << " airport has " << airportAirlines(airport) << " unique airlines that have flights to/from it.\n";
            infoCounters(airport);
        }
    }
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    airportsMenu();
}

void Manager::flightsAirportMenu() {
    system("clear");
    cout << "\tFlights by Airport Menu\n\n";
    vector<string> options { "1. Search by source airport",
                           "2. Search by target airport",
                           "3. Search by both airports",
                           "0. Go Back!" };
    for (string s : options) {
        cout << s << endl;
    }
    unsigned option;
    cout << "Select an option: ";
    cin >> option;
    switch (option) {
        case 0:
            flightsMenu();
            break;
        case 1:
            flightsSourceAirportMenu();
            break;
        case 2:
            flightsTargetAirportMenu();
            break;
        case 3:
            flightsBothAirportsMenu();
            break;
        default:
            system("clear");
            cout << "ERROR: Invalid option\n(Press any key + ENTER to continue)\n";
            string s;
            cin >> s;
            flightsAirportMenu();
    }
}

void Manager::flightsSourceAirportMenu() {
    system("clear");
    cout << "\tFlights by Source Airport Menu\n\n";
    cout << "Source airport code: ";
    string source;
    cin >> source;
    system("clear");
    for (auto node : network.getNodes()) {
        if (node.source.getCode() == source) {
            cout << "\tFlights from " << source << "\n\n";
            for (auto e : node.flights) {
                e.flight.print();
                cout << "Distance: " << (int) e.distance << " km\n\n";
            }
            break;
        }
    }
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    flightsMenu();
}

void Manager::flightsTargetAirportMenu() {
    system("clear");
    cout << "\tFlights by Target Airport Menu\n\n";
    cout << "Target airport code: ";
    string target;
    cin >> target;
    system("clear");
    bool flag = true;
    for (auto node : network.getNodes()) {
        for (auto e : node.flights) {
            if (e.flight.getTarget().getCode() == target) {
                e.flight.print();
                cout << "Distance: " << (int) e.distance << " km\n\n";
                flag = false;
            }
        }
    }
    if (flag) {
        cout << "Error: Invalid inputs\n";
    }
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    flightsMenu();
}

void Manager::flightsCityMenu() {
    system("clear");
    cout << "\tFlights by City Menu\n\n";
    cout << "(Write the cities in camel case, for example: NewYork)\n\n";
    string source, target;
    cout << "Source city: ";
    cin >> source;
    cout << "Target city: ";
    cin >> target;
    bool s, t = true;
    for (auto node : network.getNodes()) {
        if (node.source.getCity() == source) s = false;
        if (node.source.getCity() == target) t = false;
    }
    int n = 0;
    system("clear");
    if (s || t)
        cout << "Error: Invalid inputs\n";
    for (auto node : network.getNodes()) {
        if (node.source.getCity() == source) {
            for (auto e : node.flights) {
                if (e.flight.getTarget().getCity() == target) {
                    e.flight.print();
                    cout << "Distance: " << (int) e.distance << " km" << endl;
                    n++;
                }
            }
            break;
        }
    }
    if (n == 0 && !(s || t))
        cout << "There are no flights from " << source << " to " << target << endl;
    cout << "\n(Press any key + ENTER to continue)\n";
    string a;
    cin >> a;
    flightsMenu();
}

void Manager::flightsCoordinatesMenu() {
    system("clear");
    float sourceLA, targetLA, sourceLO, targetLO, range;
    cout << "\tFlights by Coordinates Menu\n\n";
    cout << "Source Latitude: ";
    cin >> sourceLA;
    cout << "Source Longitude: ";
    cin >> sourceLO;
    cout << "Target Latitude: ";
    cin >> targetLA;
    cout << "Target Latitude: ";
    cin >> targetLO;
    cout << "\nRange:";
    cin >> range;

}

void Manager::flightsBothAirportsMenu() {
    system("clear");
    cout << "\tFlights by Both Airports Menu\n\n";
    cout << "Source airport code: ";
    string source;
    cin >> source;
    cout << "Target airport code: ";
    string target;
    cin >> target;
    system("clear");
    //print flights
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    flightsMenu();
}


void Manager::airlinesMenu() {
    system("clear");
    cout << "\tAirlines Menu\n\n";
    vector<string> options{ "1. Display All Airlines",
                            "2. Browse Specific Airline",
                            "0. Go Back" };
    for (string s : options){
        cout << s << "\n";
    }
    unsigned option;
    cout << "Select an option: ";
    cin >> option;
    string aux;
    AirLine al;
    switch (option) {
        case 0:
            mainMenu();
            break;
        case 1:
            system("clear");
            for(auto t = airlines.begin() ; t!=airlines.end() ; t++){
                AirLine a=t->second;
                cout << "\nCode: " << a.getCode() << "; Name: "<< a.getName() << "\n";
            }
            cout << "\n(Press any key + ENTER to continue)\n";
            cin >> aux;
            airlinesMenu();
            break;
        case 2:
            while (airlines.find(aux) == airlines.end()) {
                system("clear");
                cout << "\tAirlines Menu\n\n";
                cout << "Airline Code: ";
                cin >> aux;
                if (airlines.find(aux) == airlines.end()) {
                    cout << "Error: Invalid airline code\n";
                    cout << "\n(Press any key + ENTER to continue)\n";
                    string a;
                    cin >> a;
                }
            }
            al = airlines[aux];
            specificAirlineMenu(al);
            break;
        default:
            system("clear");
            cout << "Error: Invalid option\n";
            cout << "(Press any key + ENTER to continue)\n";
            string a;
            cin >> a;
            airlinesMenu();
            break;
    }

}

void Manager::specificAirlineMenu(AirLine &al) {
    system("clear");
    cout << "\tAirline " << al.getName() << "Menu\n\n";
    cout << "Code: " << al.getCode() << "\n";
    cout << "Name: " << al.getName() << "\n";
    cout << "Country: " << al.getCountry() << "\n";
    cout << "Call-sign: " << al.getCallsign() << "\n";
    vector<string> options{ "1. Display all flights",
                            "0. Go Back" };
    for (string s : options) {
        cout << s << "\n";
    }
    unsigned option;
    cout << "Select an option: ";
    cin >> option;
    string aux;
    long flights;
    switch(option){
        case 0:
            airlinesMenu();
            break;
        case 1:
            system("clear");
            cout << "\tAirline " << al.getName() << "Menu\n\n";
            flights= printAirlineFlights(al);
            cout << "This airline has " << flights << " available flights!\n\n";
            cout << "(Press any key + ENTER to continue)\n";
            cin >> aux;
            airlinesMenu();
            break;
        default:
            system("clear");
            cout << "ERROR: invalid option!\n";
            cout << "(Press any key + ENTER to continue)\n";
            cin >> aux;
            specificAirlineMenu(al);
            break;
    }
}

long Manager::printAirlineFlights(AirLine &al) {
    long counter=0;
    for(Node n:network.getNodes()){
        for(Edge e:n.flights){
            if ( e.flight.getAirline().getCode() == al.getCode() ){
                e.flight.print();
                counter++;
            }
        }
    }
    return counter;
}

int Manager::airportAirlines(string airport) {
    unordered_set<string> airl;
    for (auto node: network.getNodes()) {
        if (airport == node.source.getCode()) {
            for (auto e: node.flights) {
                airl.insert(e.flight.getAirline().getCode());
            }
        }
    }
    return airl.size();
}

long Manager::countLeavingFlights(string airport) {
    for (auto node: network.getNodes()) {
        if (airport == node.source.getCode()) {
            return node.flights.size();
        }
    }
    return -1;
}

long Manager::countArrivingFlights(string airport) {
    long count = 0;
    for (auto node: network.getNodes()) {
        if (airport != node.source.getCode()) {
            for (auto e: node.flights) {
                if(e.flight.getTarget().getCode() == airport) count++;
            }
        }
    }
    return count;
}

long Manager::countDestinationsCities(string airport) {
    unordered_set<string> destinations;
    for (auto node : network.getNodes()) {
        if (airport == node.source.getCode()) {
            for (auto e : node.flights) {
                destinations.insert(e.flight.getTarget().getCity());
            }
        }
    }
    return destinations.size();
}

long Manager::countDestinationsCountries(string airport) {
    unordered_set<string> destinations;
    for (auto node : network.getNodes()) {
        if (airport == node.source.getCode()) {
            for (auto e : node.flights) {
                destinations.insert(e.flight.getTarget().getCountry());
            }
        }
    }
    return destinations.size();
}

long Manager::countArrivingCities(string airport) {
    unordered_set<string> arrivals;
    for (auto node : network.getNodes()) {
        if (airport != node.source.getCode()) {
            for (auto e : node.flights) {
                if (e.flight.getTarget().getCode() == airport) {
                    arrivals.insert(e.flight.getSource().getCity());
                }
            }
        }
    }
    return arrivals.size();
}

long Manager::countArrivingCountries(string airport) {
    unordered_set<string> arrivals;
    for (auto node : network.getNodes()) {
        if (airport != node.source.getCode()) {
            for (auto e : node.flights) {
                if (e.flight.getTarget().getCode() == airport) {
                    arrivals.insert(e.flight.getSource().getCountry());
                }
            }
        }
    }
    return arrivals.size();
}

void Manager::infoCounters(string airport) {
    long arrivingFlights = 0, leavingFlights = 0;
    unordered_set<string> arrivalsCities;
    unordered_set<string> arrivalsCountries;
    unordered_set<string> destinationsCities;
    unordered_set<string> destinationsCountries;
    for (auto node : network.getNodes()) {
        if (airport == node.source.getCode()) {
            for (auto e : node.flights) {
                destinationsCities.insert(e.flight.getTarget().getCity());
                destinationsCountries.insert(e.flight.getTarget().getCountry());
            }
            leavingFlights = node.flights.size();
        }
        else {
            for (auto e : node.flights) {
                if (e.flight.getTarget().getCode() == airport) {
                    arrivalsCities.insert(e.flight.getSource().getCity());
                    arrivalsCountries.insert(e.flight.getSource().getCountry());
                    arrivingFlights++;
                }
            }
        }
    }
    cout << "There are " << leavingFlights
         << " flights to " << destinationsCountries.size() << " countries and "
         << destinationsCities.size() << " cities that leave and " << arrivingFlights
         << " that land there, coming from "
         << arrivalsCountries.size() << " countries and "
         << arrivalsCities.size() << " cities.\n";
}
