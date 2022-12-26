#include "AirLine.h"

AirLine::AirLine(string code, string name, string callsign,string country) {
    this->code=code;
    this->name=name;
    this->callsign=callsign;
    this->country=country;
}

string AirLine::getCode() { return code; }
string AirLine::getName() { return name; }
string AirLine::getCallsign() { return callsign; }
string AirLine::getCountry() { return country; }

void AirLine::setCode(string code) { this->code=code; }
void AirLine::setName(string name) { this->name=name; }
void AirLine::setCallsign(string callsign) { this->callsign=callsign; }
void AirLine::setCountry(string country) { this->country=country; }