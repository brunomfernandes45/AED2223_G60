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
            nodes[i].source.shortPrint();
            pos = i;
            break;
        }
    }
    nodes[pos].visited = true;
    std::cout << nodes[pos].flights.size() << std::endl;
    for (auto e : nodes[pos].flights) {
        size_t w = 0;
        for (size_t i = 0; i < nodes.size(); i++) {
            if (nodes[i].source.getCode() == e.flight.getTarget().getCode()) {
                w = i;
                break;
            }
        }
        if (!nodes[w].visited) {
            dfs(nodes[w].source.getCode());
        }
    }
}

void Network::bfs(std::string start) {

}