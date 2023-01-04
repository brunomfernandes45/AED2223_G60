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
    cin >> city;
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
    for (auto &node : network.getNodes()) {
        if(node.source.getCity() == source) {
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

