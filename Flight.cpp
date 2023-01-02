#include "Flight.h"
#include <cmath>

Flight::Flight() { }

Flight::Flight(Airport source, Airport target, AirLine airline) {
    this -> source = source;
    this -> target = target;
    this -> airline = airline;
}

Airport Flight::getSource() {
    return source;
}
Airport Flight::getTarget() {
    return target;
}
AirLine Flight::getAirline() {
    return airline;
}

void Flight::setSource(Airport source) {
    this -> source = source;
}
void Flight::setTarget(Airport target) {
    this -> target = target;
}
void Flight::setAirline(AirLine airline) {
    this -> airline = airline;
}

double Flight::haversine() {
    double lat1 = source.getLatitude();
    double lon1 = source.getLongitude();
    double lat2 = target.getLatitude();
    double lon2 = target.getLongitude();

    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}