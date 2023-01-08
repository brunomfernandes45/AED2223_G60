#include "Airport.h"
#include "Flight.h"
#include <vector>
#include <list>

#ifndef AED2223_G60_NETWORK_H
#define AED2223_G60_NETWORK_H

struct Edge {
    Flight flight;
    double distance;
};

struct Node {
    Airport source;
    std::list<Edge> flights;
    bool visited;
    long dist;
    size_t prev;
    std::list<Edge>::iterator prevFlight;
};

class Network {
    std::vector<Node> nodes;
public:
    /**
     * @brief Default Constructor
     */
    Network();
    /**
     * @brief Gets the nodes vector
     * @return Returns the nodes vector
     */
    std::vector<Node> getNodes();
    /**
     * @brief Adds an airport to the nodes vector
     * Complexity: O(1)
     * @param source Airport being added to the vector
     */
    void addNode(Airport source);
    /**
     * @brief Adds a flight to the flights vector of its source airport
     * Complexity: O(n)
     * @param flight FLight being added
     */
    void addFlight(Flight flight);
    /**
     * @brief Makes a depth-first-search
     * Complexity: O(V + E), V being the number of airports and E the number of flights
     * @param start Starting position of the search
     */
    void dfs(std::string start);
    /**
     * @brief Makes a breadth-first-search
     * Complexity: O(V + E), V being the number of airports and E the number of flights
     * @param start Starting position of the search
     */
    void bfs(std::string start);
    /**
    * @brief Makes a breadth-first-search with a limited number of flights
    * Complexity: O(V + E), V being the number of airports and E the number of flights
    * @param start Starting position of the search
    * @param maxFlights Maximum of flights
    */
    void bfsSpecial(std::string start, unsigned maxFlights);
    /**
     * @brief Makes a breadth-first-search to find the best flight from an airport to another
     * @param start Source airport code
     * @param dest Target airport code
     * @param al Airline wanted
     * @return Returns a vector with the best combination of flights
     */
    std::vector<Flight> bfsBestFlights(std::string start, std::string dest,std::string al);
    // double calculateDiameter();
};


#endif //AED2223_G60_NETWORK_H
