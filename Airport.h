#include <string>
#include <vector>

#ifndef AED_G60_AIRPORT_H
#define AED_G60_AIRPORT_H


class Airport {
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;
public:
    Airport();
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude);

    std::string getCode();
    std::string getName();
    std::string getCity();
    std::string getCountry();
    double getLatitude();
    double getLongitude();

    void setCode(std::string code);
    void setName(std::string name);
    void setCity(std::string city);
    void setCountry(std::string country);
    void setLatitude(double latitude);
    void setLongitude(double longitude);

    void print();
};


#endif //AED_G60_AIRPORT_H
