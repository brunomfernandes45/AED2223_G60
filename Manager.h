#include "AirLine.h"
#include "Airport.h"
#include "Network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <unordered_map>

#ifndef AED2223_G60_MANAGER_H
#define AED2223_G60_MANAGER_H

class Manager {
    private:
        std::unordered_map<std::string, Airport> airports;
        std::unordered_map<std::string, AirLine> airlines;
        Network network;
        std::mutex airport_mutex;
        std::mutex airline_mutex;
    public:
        //readers
        void readAirlines();
        void readAirports();
        void readFlights();

        //menus
        void mainMenu();

        void airportsMenu();
        void airportsCityMenu();

        void flightsMenu();
        void flightsAirportMenu();
        void flightsCityMenu();
        void flightsCoordinatesMenu();
        void flightsSourceAirportMenu();
        void flightsTargetAirportMenu();
        void flightsBothAirportsMenu();

        void airlinesMenu();
        void specificAirlineMenu(AirLine &al);

        long printAirlineFlights(AirLine &al);
        bool isInRange(double lat, double lon, Airport &ap, double range);

};
/*
class thread_pool {
public:
    explicit thread_pool(size_t num_threads) : m_done(false) {
        for (size_t i = 0; i < num_threads; ++i) {
            m_threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(m_mutex);
                        m_cv.wait(lock, [this] { return m_done || !m_tasks.empty(); });
                        if (m_done && m_tasks.empty()) {
                            return;
                        }
                        task = std::move(m_tasks.front());
                        m_tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~thread_pool() {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_done = true;
        }
        m_cv.notify_all();
        for (std::thread& t : m_threads) {
            t.join();
        }
    }

    template <typename F>
    void enqueue(F&& f) {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_tasks.emplace(std::forward<F>(f));
        }
        m_cv.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return m_tasks.empty(); });
    }

private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_done;
};

*/
#endif //AED2223_G60_MANAGER_H
