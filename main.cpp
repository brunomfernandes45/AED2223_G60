#include "Manager.cpp"

int main() {
    Manager manager;
    manager.readAirlines();
    manager.readAirports();
    try {
        manager.readFlights();
    } catch (const invalid_argument& e) {}
    return 0;
}