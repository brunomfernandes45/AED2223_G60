#include "AirLine.h"
#include "Airport.h"

#ifndef AED_G60_FLIGHT_H
#define AED_G60_FLIGHT_H


class Flight {
    Airport source;
    Airport target;
    AirLine airline;
public:
    Flight();
    Flight(Airport source, Airport target, AirLine airline);

    Airport getSource();
    Airport getTarget();
    AirLine getAirline();

    void setSource(Airport source);
    void setTarget(Airport target);
    void setAirline(AirLine airline);

    double haversine();
};

#endif //AED_G60_FLIGHT_H
