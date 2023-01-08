#include "Network.h"
#include <queue>

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
    for(Node &n:nodes)n.visited=false;
    std::queue<size_t> q;
    size_t pos = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].source.getCode() == start) {
            //nodes[i].source.shortPrint();
            pos = i;
            break;
        }
    }
    q.push(pos);
    nodes[pos].visited=true;
    while (!q.empty()){
        int u=q.front();q.pop();
        for(auto &e:nodes[u].flights){
            size_t w;
            for(size_t i=0;i<nodes.size();i++){
                if(e.flight.getTarget().getCode()==nodes[i].source.getCode()){
                    w=i;
                    break;
                }
            }

            if(!nodes[w].visited){
                q.push(w);
                std::cout << nodes[w].source.getCode()<<"\n";
                nodes[w].visited=true;
            }

        }
    }
}