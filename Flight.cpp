#include "Flight.h"

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