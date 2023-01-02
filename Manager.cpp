#include "Manager.h"
#include "Flight.cpp"
#include "Airport.cpp"
#include "AirLine.cpp"
#include "Network.cpp"
#include <unordered_map>
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
            network.addNode(airport);
        }
    }
}

void Manager::readFlights() {
    ifstream ifs("flights.csv");
    if (ifs.is_open()) {
        string line;
        getline(ifs, line);
        unordered_map<string, Airport> airports;
        unordered_map<string, AirLine> airlines;
        size_t curr = -1;
        string aux;
        while (getline(ifs, line)) {
            istringstream iss(line);
            string from, to, code;
            getline(iss, from, ',');
            getline(iss, to, ',');
            getline(iss, code);
            if (aux != from) curr++;
            if (airports.find(from) == airports.end()) {
                Airport source = searchAirport(from);
                airports[from] = source;
            }
            if (airports.find(to) == airports.end()) {
                Airport target = searchAirport(to);
                airports[to] = target;
            }
            if (airlines.find(code) == airlines.end()) {
                AirLine airline = searchAirline(code);
                airlines[code] = airline;
            }
            Flight flight(airports[from], airports[to], airlines[code]);
            network.addFlight(curr, flight);
            aux = from;
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
    for (auto &node : network.getNodes()) {
        if (node.source.getCode() == code) return node.source;
    }
    return {};
}

void Manager::mainMenu() {
    system("clear");
    cout << "\tMain Menu\n\n";
    vector<string> options{ "1. Browse Flights",
                            "2. Browse Airports",
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
    cout << "Airport code: ";
    string code;
    cin >> code;
    Airport airport = searchAirport(code);
    system("clear");
    airport.print();
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    mainMenu();
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
            for (auto flight : node.flights) {
                flight.flight.print();
                cout << "Distance: " << flight.distance << " km\n\n";
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
    for (auto node : network.getNodes()) {
        for (auto flight : node.flights) {
            if (flight.flight.getTarget().getCode() == target) {
                flight.flight.print();
                cout << "Distance: " << flight.distance << " km\n\n";
            }
        }
    }
    cout << "\n(Press any key + ENTER to continue)\n";
    string s;
    cin >> s;
    flightsMenu();
}

void Manager::flightsCityMenu() {
    system("clear");
    string source, target;
    cout << "\tFlights by Cities Menu\n\n";
    cout << "Source City: ";
    cin >> source;
    cout << "\nTarget City: ";
    cin >> target;
    Airport s, t;
    bool sflag = true;
    bool tflag = true;
    for (auto &node : network.getNodes()){
        if(node.source.getCity() == source){
            s = node.source;
            sflag = false;
        }
        else if (node.source.getCity() == target){
            t = node.source;
            tflag = false;
        }
    }
    if(sflag || tflag){
        system("clear");
        cout << "Error: Invalid inputs!\n(Press any key + ENTER to continue)";
        string a;
        cin >> a;
        flightsMenu();
    }
    else{
        //preference
    }
}

void Manager::flightsCoordinatesMenu() {
    system("clear");
    float sourceLA, targetLA, sourceLO, targetLO, range;
    cout << "\tFlights by Coordinates Menu\n\n";
    cout << "Source Latitude: ";
    cin >> sourceLA;
    cout << "Source Longitude: ";
    cin >> sourceLO;
    cout << "\nTarget Latitude: ";
    cin >> targetLA;
    cout << "\nTarget Latitude: ";
    cin >> targetLO;
    cout << "\nRange:";
    cin >> range;

}

