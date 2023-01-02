#include "Airport.h"

Airport::Airport() { }

Airport::Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude) {
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
double Airport::getLatitude() {
    return latitude;
}
double Airport::getLongitude() {
    return longitude;
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
void Airport::setLatitude(double latitude) {
    this -> latitude = latitude;
}
void Airport::setLongitude(double longitude) {
    this -> longitude = longitude;
}

void Airport::print() {
    std::cout << "Code: " << code << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "City: " << city << std::endl;
    std::cout << "Coordinates: " << latitude << " " << longitude << std::endl;
}

