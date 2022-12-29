#include "AirLine.h"

AirLine::AirLine(std::string code, std::string name, std::string callsign, std::string country) {
    this -> code = code;
    this -> name = name;
    this -> callsign = callsign;
    this -> country = country;
}

std::string AirLine::getCode() {
    return code;
}
std::string AirLine::getName() {
    return name;
}
std::string AirLine::getCallsign() {
    return callsign;
}
std::string AirLine::getCountry() {
    return country;
}

void AirLine::setCode(std::string code) {
    this -> code = code;
}
void AirLine::setName(std::string name) {
    this -> name = name;
}
void AirLine::setCallsign(std::string callsign) {
    this -> callsign = callsign;
}
void AirLine::setCountry(std::string country) {
    this -> country = country;
}