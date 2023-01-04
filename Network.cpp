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

void Network::dfs(std::string start) {
    size_t pos = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].source.getCode() == start) {
            pos = i;
            break;
        }
    }
    nodes[pos].source.shortPrint();
    nodes[pos].visited = true;
    for (auto e : nodes[pos].flights) {
        size_t dest = 0;
        for (size_t i = 0; i < nodes.size(); i++) {
            if (nodes[i].source.getCode() == start) {
                dest = i;
                break;
            }
        }
        if (!nodes[dest].visited) {
            dfs(nodes[dest].source.getCode());
        }
    }
}

void Network::bfs(std::string start) {

}