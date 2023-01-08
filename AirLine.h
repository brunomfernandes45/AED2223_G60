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
        /**
         * @brief Default constructor
         */
        AirLine();
        /**
         * @brief Constructor of an Airline
         * @param code Airline's code
         * @param name Airline's name
         * @param callsign Airline's call-sign
         * @param country Airline's country
         */
        AirLine(std::string code, std::string name, std::string callsign, std::string country);

        /**
         * @brief Gets the airline's code
         * @return Returns the airline's code
         */
        std::string getCode();
        /**
         * @brief Gets the airline's name
         * @return Returns the airline's name
         */
        std::string getName();
        /**
         * @brief Gets the airline's call-sign
         * @return Returns the airline's call-sign
         */
        std::string getCallsign();
        /**
         * @brief Gets the airline's country
         * @return Returns the airline's country
         */
        std::string getCountry();

        /**
        * @brief Sets the airline's code
        * @param code code being set
        */
        void setCode(std::string code);
        /**
        * @brief Sets the airline's name
        * @param name name being set
        */
        void setName(std::string name);
        /**
        * @brief Sets the airline's call-sign
        * @param callsign call-sign being set
        */
        void setCallsign(std::string callsign);
        /**
        * @brief Sets the airline's country
        * @param country country being set
        */
        void setCountry(std::string country);
};

#endif //AED_G60_AIRLINE_H
