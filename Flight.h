#include "AirLine.h"
#include "Airport.h"

#ifndef AED_G60_FLIGHT_H
#define AED_G60_FLIGHT_H


class Flight {
    Airport source;
    Airport target;
    AirLine airline;
public:
    /**
     * @brief Default constructor
     */
    Flight();
    /**
     * @brief Constructor of a flight
     * @param source The flight's source airport
     * @param target The flight's target airport
     * @param airline The flight's airline
     */
    Flight(Airport source, Airport target, AirLine airline);

    /**
     * @brief Gets the source airport
     * @return Returns the source airport
     */
    Airport getSource();
    /**
    * @brief Gets the target airport
    * @return Returns the target airport
    */
    Airport getTarget();
    /**
    * @brief Gets the airline
    * @return Returns the airline
    */
    AirLine getAirline();

    /**
     * @brief Sets the source airport
     * @param source Airport being set as source
     */
    void setSource(Airport source);
    /**
    * @brief Sets the target airport
    * @param target Airport being set as target
    */
    void setTarget(Airport target);
    /**
     * @brief Sets the airline
     * @param airline Airline begin set
     */
    void setAirline(AirLine airline);
    /**
     * @brief Prints the flight's information
     * Complexity: O(1)
     */
    void print();

    /**
     * @brief Calculates the distance between the source and the target airport using the Haversine formula
     * Complexity: O(1)
     * @return Returns the distance between the source and the target airport
     */
    double haversine();
};

#endif //AED_G60_FLIGHT_H
