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
    Network();
    std::vector<Node> getNodes();
    void addNode(Airport source);
    void addFlight(Flight flight);
    void dfs(std::string start);
    void bfs(std::string start);
    void bfsSpecial(std::string start, unsigned maxFlights);
    std::vector<Flight> bfsBestFlights(std::string start, std::string dest);
    // double calculateDiameter();
};


#endif //AED2223_G60_NETWORK_H
