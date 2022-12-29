#include "Flight.h"
#include <string>
#include <vector>

#ifndef AED_G60_AIRPORT_H
#define AED_G60_AIRPORT_H


class Airport {
    private:
        std::string code;
        std::string name;
        std::string city;
        std::string country;
        float latitude;
        float longitude;
        std::vector<Flight> flights;
    public:
        Airport();
        Airport(std::string code, std::string name, std::string city, std::string country, float latitude, float longitude);

        std::string getCode();
        std::string getName();
        std::string getCity();
        std::string getCountry();
        float getLatitude();
        float getLongitude();
        std::vector<Flight> getFlights();

        void setCode(std::string code);
        void setName(std::string name);
        void setCity(std::string city);
        void setCountry(std::string country);
        void setLatitude(float latitude);
        void setLongitude(float longitude);
        void setFlights(std::vector<Flight> flights);

        void addFlight(Flight flight);
};


#endif //AED_G60_AIRPORT_H
