#include "Manager.h"
#include "Flight.cpp"
#include "Airport.cpp"
#include "AirLine.cpp"
#include "Network.cpp"
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
            //airportsCountryMenu();
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
    cout << "Enter a city: ";
    getline(cin, city);
    for (auto node:network.getNodes()) {
        if (city == node.source.getCity()) {
            node.source.shortPrint();
            n++;
        }
    }
    if (n > 0)
        cout << "Number of airports in " << city << ": " << n << endl;
    else
        cout << "No airports found in this city\n";
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
    getline(cin, source);
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
    getline(cin, target);
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
    string op1, op2, source, target;
    cout << "Does the source city have more than one word? [y / n] ";
    cin >> op1;
    system("clear");
    cout << "Source city: ";
    if (op1 == "y") {
        getline(cin, source);
        cout << endl;
    }
    else {
        cin >> source;
    }
    cin >> op2;
    system("clear");
    cout << "Target city: ";
    if (op2 == "y") {
        getline(cin, target);
        cout << endl;
    }
    else {
        cin >> target;
    }
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
    cout << "Source airport code: ";
    string source;
    getline(cin, source);
    cout << "You entered: " << source << endl;
    cout << "Target airport code: ";
    string target;
    getline(cin, target);
    cout << "You entered: " << target << endl;
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
            cout << "\tAirlines Menu\n\n";
            for(auto t = airlines.begin() ; t!=airlines.end() ; t++){
                AirLine a=t->second;
                cout << "\nCode: " << a.getCode() << "; Name: "<< a.getName() << "\n";
            }
            cout << "\n(Press any key + ENTER to continue)\n";
            cin >> aux;
            airlinesMenu();
            break;
        case 2:
            system("clear");
            cout << "\tAirlines Menu\n\n";
            cout << "Airline Code: ";
            cin >> aux;
            al = airlines[aux];
            specificAirlineMenu(al);
            break;
        default:
            system("clear");
            cout << "ERROR: invalid option!\n";
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
    for (string s : options){
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


