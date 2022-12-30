 #include "AirLine.h"

#ifndef AED_G60_FLIGHT_H
#define AED_G60_FLIGHT_H


class Flight {
    private:
        std::string source;
        std::string target;
        AirLine airline;
    public:
        Flight(std::string source, std::string target, AirLine airline);

        std::string getSource();
        std::string getTarget();
        AirLine getAirline();

        void setSource(std::string source);
        void setTarget(std::string target);
        void setAirline(AirLine airline);
};

.
#endif //AED_G60_FLIGHT_H
