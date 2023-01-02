#include "Network.h"

Network::Network() {
    nodes.reserve(3019);
}

void Network::addNode(Airport source) {
    Node newNode { source };
    nodes.push_back(newNode);
}

std::vector<Node> Network::getNodes() {
    return nodes;
}

void Network::addFlight(size_t pos, Flight flight) {
    Edge newEdge { flight, flight.haversine() };
    nodes[pos].flights.push_back(newEdge);
}

void Network::dfs(int start) {

}

void Network::bfs(int start) {

}