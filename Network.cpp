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

void Network::addFlight(Flight flight) {
    Edge newEdge { flight, flight.haversine() };
    for (auto &node : nodes) {
        if (node.source.getCode() == flight.getSource().getCode()) {
            node.flights.push_back(newEdge);
            break;
        }
    }
}

void Network::dfs(int start) {

}

void Network::bfs(int start) {

}