#include "AirLine.h"
#include "Airport.h"

#ifndef AED_G60_FLIGHT_H
#define AED_G60_FLIGHT_H


class Flight {
    private:
        Airport source;
        Airport target;
        AirLine airline;
    public:
        Flight(Airport source, Airport target, AirLine airline);

        Airport getSource();
        Airport getTarget();
        AirLine getAirline();

        void setSource(Airport source);
        void setTarget(Airport target);
        void setAirline(AirLine airline);
};


#endif //AED_G60_FLIGHT_H
