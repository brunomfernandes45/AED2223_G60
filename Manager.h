#include "AirLine.h"
#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Network.h"

#ifndef AED2223_G60_MANAGER_H
#define AED2223_G60_MANAGER_H

class Manager {
    private:
        std::vector<AirLine> airlines;
        Network network;
    public:
        //readers
        void readAirlines();
        void readAirports();
        void readFlights();

        //searches
        AirLine searchAirline(std::string code);
        Airport searchAirport(std::string code);


        //menus
        void mainMenu();
        void flightsMenu();
        void airportsMenu();
        void flightsAirportMenu();
        void flightsCityMenu();
        void flightsCoordinatesMenu();
        void flightsSourceAirportMenu();
        void flightsTargetAirportMenu();
        void flightsBothAirportsMenu();

};

#endif //AED2223_G60_MANAGER_H
