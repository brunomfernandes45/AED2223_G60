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
    /**
     * @brief Default Contructor
     */
    Airport();
    /**
     * Constructor of an airport
     * @param code Airport's code
     * @param name Airport's name
     * @param city Airport's city
     * @param country Airport's country
     * @param latitude Airport's latitude
     * @param longitude Airport's longitude
     */
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude);

    /**
     * @brief Gets the airport's code
     * @return Returns the airport's code
     */
    std::string getCode();
    /**
     * @brief Gets the airport's name
     * @return Returns the airport's name
     */
    std::string getName();
    /**
     * @brief Gets the airport's city
     * @return Returns the airport's city
     */
    std::string getCity();
    /**
     * @brief Gets the airport's country
     * @return Returns the airport's country
     */
    std::string getCountry();
    /**
     * @brief Gets the airport's latitude
     * @return Returns the airport's latitude
     */
    double getLatitude();
    /**
     * @brief Gets the airport's longitude
     * @return Returns the airport's longitude
     */
    double getLongitude();

    /**
     * @brief Sets the airport's code
     * @param code Code being set
     */
    void setCode(std::string code);
    /**
     * @brief Sets the airport's name
     * @param name Name being set
     */
    void setName(std::string name);
    /**
     * @brief Sets the airport's city
     * @param city City being set
     */
    void setCity(std::string city);
    /**
     * @brief Sets the airport's country
     * @param country Country being set
     */
    void setCountry(std::string country);
    /**
     * @brief Sets the airport's latitude
     * @param latitude Latitude being set
     */
    void setLatitude(double latitude);
    /**
     * @brief Sets the airport's longitude
     * @param longitude Longitude being set
     */
    void setLongitude(double longitude);

    /**
     * @brief Prints the airport's information
     * Complexity: O(1)
     */
    void print();
    /**
     * @brief Prints the airport's information in one line
     * Complexity: O(1)
     */
    void shortPrint();
};


#endif //AED_G60_AIRPORT_H
