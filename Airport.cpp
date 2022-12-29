#include "Airport.h"

Airport::Airport() { }

Airport::Airport(std::string code, std::string name, std::string city, std::string country, float latitude, float longitude) {
    this -> code = code;
    this -> name = name;
    this -> city = city;
    this -> country = country;
    this -> latitude = latitude;
    this -> longitude = longitude;
}

std::string Airport::getCode() {
    return code;
}
std::string Airport::getName() {
    return name;
}
std::string Airport::getCity() {
    return city;
}
std::string Airport::getCountry() {
    return country;
}
float Airport::getLatitude() {
    return latitude;
}
float Airport::getLongitude() {
    return longitude;
}
std::vector<Flight> Airport::getFlights() {
    return flights;
}

void Airport::setCode(std::string code) {
    this -> code = code;
}
void Airport::setName(std::string name) {
    this -> name = name;
}
void Airport::setCity(std::string city) {
    this -> city = city;
}
void Airport::setCountry(std::string country) {
    this -> country = country;
}
void Airport::setLatitude(float latitude) {
    this -> latitude = latitude;
}
void Airport::setLongitude(float longitude) {
    this -> longitude = longitude;
}

void Airport::setFlights(std::vector<Flight> flights) {
    this -> flights = flights;
}

void Airport::addFlight(Flight flight) {
    flights.push_back(flight);
}

