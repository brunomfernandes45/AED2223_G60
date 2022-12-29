#include "Flight.h"

Flight::Flight(std::string source, std::string target, AirLine airline) {
    this -> source = source;
    this -> target = target;
    this -> airline = airline;
}

std::string Flight::getSource() {
    return source;
}
std::string Flight::getTarget() {
    return target;
}
AirLine Flight::getAirline() {
    return airline;
}

void Flight::setSource(std::string source) {
    this -> source = source;
}
void Flight::setTarget(std::string target) {
    this -> target = target;
}
void Flight::setAirline(AirLine airline) {
    this -> airline = airline;
}