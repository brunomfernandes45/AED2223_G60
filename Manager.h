#include "AirLine.h"
#include "Airport.h"
#include "Network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#ifndef AED2223_G60_MANAGER_H
#define AED2223_G60_MANAGER_H

class Manager {
private:
    std::unordered_map<std::string, Airport> airports;
    std::unordered_map<std::string, AirLine> airlines;
    Network network;
public:
    /**
     * @brief Removes white spaces from strings
     * Complexity: O(n)
     * @param str
     */
    void removeWhitespace(std::string& str);

    /**
     * @brief Reads the file airlines.csv
     * Complexity: O(n)
     */
    void readAirlines();
    /**
    * @brief Reads the file airports.csv
    * Complexity: O(n)
    */
    void readAirports();
    /**
    * @brief Reads the file flights.csv
    * Complexity: O(n)
    */
    void readFlights();

    /**
     * @brief Displays the main menu
     */
    void mainMenu();

    /**
    * @brief Displays the airports menu
    */
    void airportsMenu();
    /**
     * @brief Displays the airports by name Menu
     */
    void airportsNameMenu();
    /**
     * @brief Displays the airports by city menu
     */
    void airportsCityMenu();
    /**
     * @brief Displays the airports by country menu
     */
    void airportsCountryMenu();
    /**
     * @brief Searches for a specific airport
     * Complexity: O(n), n being the number of airports
     */
    void searchForAirport();
    /**
     * @brief Displays the nFlights menu
     */
    void nFlightsMenu();

    /**
     * @brief Displays the Flights menu
     */
    void flightsMenu();
    /**
     * @brief Displays the Flights by airport menu
     */
    void flightsAirportMenu();
    /**
     * @brief Displays the Flights by city menu
     */
    void flightsCityMenu();
    /**
     * @brief Displays the Flights by coordinates menu
     */
    void flightsCoordinatesMenu();
    /**
     * @brief Displays the Flights that depart from a certain airport
     * Complexity: O(n * e), n being the airports and e being the flights
     */
    void flightsSourceAirportMenu();
    /**
    * @brief Displays the Flights that arrive at a certain airport
    * Complexity: O(n * e), n being the airports and e being the flights
    */
    void flightsTargetAirportMenu();
    /**
    * @brief Displays the Flights that depart and arrive at certain airports
    * Complexity: O(n * e), n being the airports and e being the flights
    */
    void flightsBothAirportsMenu();

    /**
     * @brief Displays the airlines menu
     */
    void airlinesMenu();
    /**
     * @brief Displays the specific airline menu
     * @param al airline being browsed
     */
    void specificAirlineMenu(AirLine &al);

    /**
     * @brief Displays the stats menu
     */
    void statsMenu();
    /**
     * @brief Displays the global stats menu
     */
    void globalStatsMenu();
    /**
     * @brief Displays the country stats menu
     */
    void countryStatsMenu();

    /**
     * @brief Prints all the flights of an airline
     * Complexity: O(n * e), n being the airports and e the flights
     * @param al Airline of the flights being printed
     * @return Return the total flights printed
     */
    long printAirlineFlights(AirLine &al);
    /**
     * @brief Returns the number of airlines with flights leaving a specific airport
     * Complexity: O(n * e), n being the airports and e the flights
     * @param airport Airport from where the flights of each airline are leaving
     * @return Returns the number of different airlines
     */
    int airportAirlines(std::string airport);
    /**
     * @brief Checks if an airport is in certain range of a certain location
     * Complexity: O(1), n being the airports and e the flights
     * @param lat Location's Latitude
     * @param lon Location's Longitude
     * @param ap Airport being compared
     * @param range Search range
     * @return Returns true if the airport ap is in the range of the location
     */
    bool isInRange(double lat, double lon, Airport &ap, double range);
    /**
     * @brief Displays the counts of the arriving flights, leaving flights, destination countries, destination cities, arrival countries and arrival cities of an airport
     * Complexity: O(n * e), n being the airports and e the flights
     * @param airport Airport being studied
     */
    void infoCounters(std::string airport);
};

#endif //AED2223_G60_MANAGER_H
