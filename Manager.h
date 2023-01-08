#include "AirLine.h"
#include "Airport.h"
#include "Network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#ifndef AED2223_G60_MANAGER_H
#define AED2223_G60_MANAGER_H

class Manager {
private:
    std::unordered_map<std::string, Airport> airports;
    std::unordered_map<std::string, AirLine> airlines;
    Network network;
public:
    void readAirlines();
    void readAirports();
    void readFlights();

    void mainMenu();

    void airportsMenu();
    void airportsNameMenu();
    void airportsCityMenu();
    void airportsCountryMenu();
    void searchForAirport();
    void nFlightsMenu();

    void flightsMenu();
    void flightsAirportMenu();
    void flightsCityMenu();
    void flightsCoordinatesMenu();
    void flightsSourceAirportMenu();
    void flightsTargetAirportMenu();
    void flightsBothAirportsMenu();

    void airlinesMenu();
    void specificAirlineMenu(AirLine &al);

    void statsMenu();
    void globalStatsMenu();
    void countryStatsMenu();
    void airlineStatsMenu();

    long printAirlineFlights(AirLine &al);
    int airportAirlines(std::string airport);
    bool isInRange(double lat, double lon, Airport &ap, double range);
    void infoCounters(std::string airport);
};

#endif //AED2223_G60_MANAGER_H
