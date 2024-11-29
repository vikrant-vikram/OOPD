#include "includes.h"  // Include constants and macros
#include "base.cpp"    // Include Packet and User classes
#include "constants.h" // Include constants
using namespace std;
class AccessPoint {
private:
    double current_time;      // Tracks current time in the simulation
    double total_throughput;  // Total data successfully transmitted
    vector<double> latencies; // Stores latencies of transmitted packets

    // Generates a random backoff time (microseconds)
    int getRandomBackoffTime() {
        return rand() % MAX_BACKOFF_TIME + 1;
    }

public:
    AccessPoint() : current_time(0.0), total_throughput(0.0) {}

    // Simulates the communication for a set of users
    void simulate(vector<User>& users) {
        while (true) {
            bool all_done = true;

            for (auto& user : users) {
                if (!user.packets.empty()) {
                    all_done = false;

                    // Transmit the packet
                    Packet packet = user.packets.front();
                    if (current_time < packet.arrival_time) {
                        current_time = packet.arrival_time;
                    }

                    double transmission_time = packet.size * 8 / DATA_RATE; // Time to transmit packet
                    current_time += transmission_time;

                    total_throughput += packet.size; // Update total throughput

                    double latency = current_time - packet.arrival_time;
                    latencies.push_back(latency);

                    user.packets.pop(); // Remove the transmitted packet
                }
            }

            if (all_done) break; // Exit if all packets are transmitted
        }
    }

    // Prints the results of the simulation in a specific color
    void printResults(int num_users, const string& color) {
        double average_latency = accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
        double max_latency = *max_element(latencies.begin(), latencies.end());
        double throughput = total_throughput / current_time; // Throughput in bytes per second

        cout << color << "WiFi 4 Simulation with " << num_users << " users:" << RESET << "\n";
        cout << color << "Throughput: " << throughput / 1e6 << " MB/s" << RESET << "\n";
        cout << color << "Average Latency: " << average_latency << " seconds" << RESET << "\n";
        cout << color << "Maximum Latency: " << max_latency << " seconds" << RESET << "\n";
        cout << color << "Total Simulation Time: " << current_time << " seconds" << RESET << "\n\n";
    }
};


int main() {
    srand(time(0)); // Seed random number generator

    cout << CYAN << "WiFi 4 Simulation Results:" << RESET << "\n";
    cout << "---------------------------------------------\n";

    // Case 1: 1 user and 1 AP
    {
        vector<User> users;
        users.emplace_back(0); // Create a single user
        users[0].generatePackets(10, 0.0); // Generate 10 packets

        AccessPoint ap;
        ap.simulate(users);
        ap.printResults(1, CYAN); // Print results in CYAN
    }

    // Case 2: 10 users and 1 AP
    {
        vector<User> users;
        for (int i = 0; i < 10; ++i) {
            users.emplace_back(i); // Create 10 users
            users[i].generatePackets(10, 0.0); // Each generates 10 packets
        }

        AccessPoint ap;
        ap.simulate(users);
        ap.printResults(10, MAGENTA); // Print results in MAGENTA
    }

    // Case 3: 100 users and 1 AP
    {
        vector<User> users;
        for (int i = 0; i < 100; ++i) {
            users.emplace_back(i); // Create 100 users
            users[i].generatePackets(10, 0.0); // Each generates 10 packets
        }

        AccessPoint ap;
        ap.simulate(users);
        ap.printResults(100, CYAN); // Print results in CYAN
    }

    return 0;
}
