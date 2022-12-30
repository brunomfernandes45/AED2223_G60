#include "AirLine.h"
#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifndef AED2223_G60_MANAGER_H
#define AED2223_G60_MANAGER_H

class Manager {
    private:
        std::vector<AirLine> airlines;
        std::vector<Airport> airports;
    public:
        //readers
        void readAirlines();
        void readAirports();
        void readFlights();

        //searches
        AirLine searchAirline(std::string code);
        Airport searchAirport(std::string code);


        //menus
        void fetchingmenu();
        void mainmenu();
        void flightsmenu();
        void airportsmenu();

};

#endif //AED2223_G60_MANAGER_H
