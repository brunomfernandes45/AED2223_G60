#include "Manager.cpp"

int main() {
    Manager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();
    manager.mainMenu();
    return 0;
}