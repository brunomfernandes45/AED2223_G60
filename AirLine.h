#include <string>

#ifndef AED_G60_AIRLINE_H
#define AED_G60_AIRLINE_H

class AirLine {
    private:
        std::string code;
        std::string name;
        std::string callsign;
        std::string country;
    public:
        AirLine();
        AirLine(std::string code, std::string name, std::string callsign, std::string country);

        std::string getCode();
        std::string getName();
        std::string getCallsign();
        std::string getCountry();

        void setCode(std::string code);
        void setName(std::string name);
        void setCallsign(std::string callsign);
        void setCountry(std::string country);
};

#endif //AED_G60_AIRLINE_H
