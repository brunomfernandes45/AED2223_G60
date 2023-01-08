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
        //readers
        void readAirlines();
        void readAirports();
        void readFlights();

        //menus
        void mainMenu();

        void airportsMenu();
        void airportsCityMenu();
        void airportsCountryMenu();
        void searchForAirport();

        void flightsMenu();
        void flightsAirportMenu();
        void flightsCityMenu();
        void flightsCoordinatesMenu();
        void flightsSourceAirportMenu();
        void flightsTargetAirportMenu();
        void flightsBothAirportsMenu();

        void airlinesMenu();
        void specificAirlineMenu(AirLine &al);

        long printAirlineFlights(AirLine &al);
        int airportAirlines(std::string airport);
        bool isInRange(double lat, double lon, Airport &ap, double range);

        long countLeavingFlights(std::string airport);
        long countArrivingFlights(std::string airport);
        long countDestinationsCountries(std::string airport);
        long countDestinationsCities(std::string airport);
        long countArrivingCountries(std::string airport);
        long countArrivingCities(std::string airport);

};

#endif //AED2223_G60_MANAGER_H
