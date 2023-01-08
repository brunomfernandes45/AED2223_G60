#include "Network.h"
#include <queue>
#include <unordered_map>
#include <set>
#include <unordered_set>

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

            if(!nodes[w].visited) {
                q.push(w);
                nodes[w].visited=true;
            }
        }
    }
}

void Network::bfsSpecial(std::string start, unsigned maxFlights) {
    for (Node &n:nodes) n.visited = false;
    std::queue<size_t> q;
    std::unordered_set<size_t> airports;
    std::unordered_set<std::string> cities;
    std::unordered_set<std::string> countries;
    size_t pos = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].source.getCode() == start) {
            pos = i;
            break;
        }
    }
    q.push(pos);
    nodes[pos].visited=true;
    nodes[pos].dist = 0;
    while (!q.empty() && nodes[q.front()].dist < maxFlights) {
        int u=q.front();q.pop();
        for(auto &e:nodes[u].flights){
            size_t w;
            for(size_t i=0;i<nodes.size();i++){
                if(e.flight.getTarget().getCode()==nodes[i].source.getCode()){
                    w=i;
                    break;
                }
            }

            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].dist = nodes[u].dist + 1;
                nodes[w].visited = true;
                airports.insert(w);
                cities.insert(nodes[w].source.getCity());
                countries.insert(nodes[w].source.getCountry());
            }
        }
    }
    std::cout << "From " << nodes[pos].source.getName() << " airport, using a maximum of "
    << maxFlights << " flights, you can reach " << countries.size() << " countries, "
    << cities.size() << " cities and " << airports.size() << " airports.\n";
}

std::vector<Flight> Network::bfsBestFlights(std::string start, std::string dest,std::string al) {
    for (Node &n:nodes) n.visited = false;
    std::queue<size_t> q;
    size_t startPos = 0;
    size_t destPos = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].source.getCode() == start) {
            startPos = i;
        }
        if (nodes[i].source.getCode() == dest) {
            destPos = i;
        }
    }
    q.push(startPos);
    nodes[startPos].visited = true;
    nodes[startPos].prevFlight = nodes[startPos].flights.end();
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (nodes[u].source.getCode() == dest) {
            std::vector<Flight> result;
            int curr = u;
            auto flightIt = nodes[curr].prevFlight;
            while (flightIt != nodes[curr].flights.end()) {
                result.insert(result.begin(), flightIt -> flight);
                curr = nodes[curr].prev;
                flightIt = nodes[curr].prevFlight;
            }
            return result;
        }
        for(auto flightIt = nodes[u].flights.begin(); flightIt != nodes[u].flights.end(); flightIt++) {
            if(flightIt->flight.getAirline().getCode() != al && al!="000")continue;
            size_t w;
            for(size_t j = 0; j < nodes.size(); j++){
                if(flightIt->flight.getTarget().getCode() == nodes[j].source.getCode()){
                    w = j;
                    break;
                }
            }
            if(!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].prev = u;
                nodes[w].prevFlight = flightIt;
            }
        }
    }
    return std::vector<Flight>();
}



/*
double Network::calculateDiameter() {
    double maxDiameter = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        std::unordered_map<size_t, double> distances;
        std::priority_queue<std::pair<double, size_t>, std::vector<std::pair<double, size_t>>, std::greater<std::pair<double, size_t>>> pq;

        // initialize distances and priority queue
        for (size_t j = 0; j < nodes.size(); j++) {
            distances[j] = std::numeric_limits<double>::infinity();
        }
        distances[i] = 0;
        pq.push({0, i});

        // Dijkstra's algorithm
        while (!pq.empty()) {
            size_t u = pq.top().second;
            pq.pop();

            for (auto &e : nodes[u].flights) {
                size_t v;
                for (size_t k = 0; k < nodes.size(); k++) {
                    if (e.flight.getTarget().getCode() == nodes[k].source.getCode()) {
                        v = k;
                        break;
                    }
                }
                double distance = e.distance;
                if (distances[v] > distances[u] + distance) {
                    distances[v] = distances[u] + distance;
                    pq.push({distances[v], v});
                }
            }
        }

        // find maximum distance from source node
        for (const auto &pair : distances) {
            double distance = pair.second;
            if (distance > maxDiameter) {
                maxDiameter = distance;
            }
        }
    }
    return maxDiameter;
} */






