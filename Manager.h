#include "AirLine.cpp"
#include "Airport.cpp"
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
        void readAirlines();
        void readAirports();
};


#endif //AED2223_G60_MANAGER_H
