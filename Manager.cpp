#include "Manager.h"
#include "Flight.cpp"
#include "Airport.cpp"
#include "AirLine.cpp"
#include "Network.cpp"
#include <unordered_set>
#include <algorithm>

using namespace std;

void Manager::removeWhitespace(string& str) {
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
                            "4. Statistics",
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
        case 4:
            statsMenu();
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
    vector<string> options{ "1. Search airport by name",
                            "2. Browse Airports per city",
                            "3. Browse Airports per country",
                            "4. Detailed info about an airport",
                            "5. See where you can go using n flights",
                            "0. Go Back!" };
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
            airportsNameMenu();
            break;
        case 2:
            airportsCityMenu();
            break;
        case 3:
            airportsCountryMenu();
            break;
        case 4:
            searchForAirport();
            break;
        case 5:
            nFlightsMenu();
            break;
        default:
            system("clear");
            cout << "ERROR: Invalid option\n(Press any key + ENTER to continue)\n";
            string s;
            cin >> s;
            airportsMenu();
    }
}

void Manager::airportsNameMenu() {
    system("clear");
    cout << "\tAirports by Name Menu\n\n";
    cout << "(Write the name in camel case, for example: JohnFKennedyIntl)\n\n";
    string name;
    cout << "Insert the name of the airport: ";
    cin >> name;
    bool flag = true;
    for (auto node : network.getNodes()) {
        if (node.source.getName() == name) {
            node.source.print();
            flag = false;
            break;
        }
    }
    if (flag) {
        system("clear");
        cout << "Error: Invalid name\n";
    }
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    airportsMenu();
}

void Manager::airportsCityMenu() {
    string city;
    int n = 0;
    system("clear");
    cout << "\tAirports by City Menu\n\n";
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

void Manager::nFlightsMenu() {
    system("clear");
    string source;
    cout << "Insert source airport code: ";
    cin >> source;
    unsigned maxFlights;
    cout << "Insert maximum flights: ";
    cin >> maxFlights;
    network.bfsSpecial(source, maxFlights);
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
        default:
            system("clear");
            cout << "Error: Invalid option\n(Press any key + ENTER to continue)\n";
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
    long nFlights;
    bool flag = true;
    for (auto node : network.getNodes()) {
        if (node.source.getCode() == source) {
            cout << "\tFlights from " << source << "\n\n";
            for (auto e : node.flights) {
                e.flight.print();
                cout << "Distance: " << (int) e.distance << " km\n\n";
                flag = false;
            }
            nFlights = node.flights.size();
            break;
        }
    }
    if (flag)
        cout << "Error: Invalid inputs\n";
    else
        cout << "There are " << nFlights << " flights that leave this airport.\n";
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    flightsAirportMenu();
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
    if (flag)
        cout << "Error: Invalid inputs\n";
    else
        cout << "There are " << nFlights << " flights that leave this airport.\n";
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    flightsAirportMenu();
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
    double sourceLA, targetLA, sourceLO, targetLO, range;
    cout << "\tFlights by Coordinates Menu\n\n";
    cout << "Source Latitude: ";
    cin >> sourceLA;
    cout << "Source Longitude: ";
    cin >> sourceLO;
    cout << "Target Latitude: ";
    cin >> targetLA;
    cout << "Target Latitude: ";
    cin >> targetLO;
    cout << "Range: ";
    cin >> range;
    system("clear");
    vector< vector<Flight> > flights;
    vector<string> sources, targets;
    for (auto &node : network.getNodes()) {
        if (isInRange(sourceLA, sourceLO, node.source, range)) {
            sources.push_back(node.source.getCode());
        }
        if (isInRange(targetLA, targetLO, node.source, range)) {
            targets.push_back(node.source.getCode());
        }
    }
    for (auto s : sources) {
        for (auto t : targets) {
            auto v = network.bfsBestFlights(s, t);
            if (v.empty()) continue;
            flights.push_back(v);
        }
    }
    sort(flights.begin(), flights.end(), [](vector<Flight> v1, vector<Flight> v2) {
        return (v1.size() < v2.size());
    });
    if (!flights.empty()) {
        cout << "Best flights to take: \n";
        size_t minFlights = flights[0].size();
        for (size_t i = 0; i < flights.size(); i++) {
            if (flights[i].size() == minFlights) {
                for (size_t j = 0; j < flights[i].size(); j++) {
                    flights[i][j].print();
                }
                cout << endl;
            }
        }
    }
    else
        cout << "There is no way to get from source coordinates to target coordinates within " << range << " km.\n";
    cout << "\n(Press any key + ENTER to continue)\n";
    string a;
    cin >> a;
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
    cout << "Call-sign: " << al.getCallsign() << "\n\n";
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

void Manager::statsMenu() {
    system("clear");
    cout << "\tStats Menu\n\n";
    vector<string> options { "1. Global network statistics",
                             "2. Country statistics",
                             "0. Go back"};
    for (string s : options) {
        cout << s << endl;
    }
    unsigned option;
    cout << "Select an option: ";
    cin >> option;
    switch (option) {
        case 0:
            mainMenu();
            break;
        case 1:
            globalStatsMenu();
            break;
        case 2:
            countryStatsMenu();
            break;
        default:
            system("clear");
            cout << "ERROR: invalid option!\n";
            cout << "(Press any key + ENTER to continue)\n";
            string a;
            cin >> a;
            statsMenu();
            break;
    }
}

void Manager::globalStatsMenu() {
    system("clear");
    cout << "\tGlobal Statistics\n\n";
    cout << "(Press any key + ENTER to continue)\n";
    string a;
    cin >> a;
    statsMenu();
}

void Manager::countryStatsMenu() {
    system("clear");
    cout << "\tCountry Stats Menu\n\n";
    cout << "(Write the countries in camel case, for example: UnitedStates)\n\n";
    string country;
    cout << "Insert the country: ";
    cin >> country;
    long arrivingFlights, departingFlights, al=0;
    for( Node n: network.getNodes() ){
        for(Edge f : n.flights){
            if( f.flight.getSource().getCountry()==country) departingFlights++;
            else if ( f.flight.getTarget().getCountry()==country ) arrivingFlights++;
        }
    }
    for(auto it=airlines.begin();it!=airlines.end();it++){
        if(it->second.getCountry()==country) al++;
    }
    cout << "Airlines: " << al << "\nDeparting Flights: " << departingFlights << "\nArriving Flights: " << arrivingFlights << "\n";
    cout << "(Press any key + ENTER to continue)\n";
    string a;
    cin >> a;
    statsMenu();
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
