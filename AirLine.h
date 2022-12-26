
#include <string>

using namespace std;
#ifndef AED_G60_AIRLINE_H
#define AED_G60_AIRLINE_H


class AirLine {
private:

    string code;
    string name;
    string callsign;
    string country;

    //Constructor
    AirLine(string code, string name, string callsign,string country);

    //getters
    string getCode();
    string getName();
    string getCallsign();
    string getCountry();

    //setters
    void setCode(string code);
    void setName(string name);
    void setCallsign(string callsign);
    void setCountry(string country);
};


#endif //AED_G60_AIRLINE_H
