
#include "includes.h"  // Include the constants and necessary header files
#include "base.cpp"    // Include Packet and User class
#include "constants.h" // Include the constants header file
class AccessPoint {
private:
    double current_time;      // Tracks the current time in the simulation
    double total_throughput;  // Total data successfully transmitted
    std::vector<double> latencies; // Stores latencies of transmitted packets

    // Generates a random backoff time (microseconds)
    int getRandomBackoffTime() {
        return rand() % MAX_BACKOFF_TIME + 1;
    }

public:
    AccessPoint() : current_time(0.0), total_throughput(0.0) {}

    // Simulates communication for a set of users
    void simulate(std::vector<User>& users) {
        while (true) {
            bool all_done = true;

            for (auto& user : users) {
                if (!user.packets.empty()) {
                    all_done = false;

                    // Attempt to transmit the packet
                    Packet packet = user.packets.front();
                    if (current_time < packet.arrival_time) {
                        current_time = packet.arrival_time;
                    }

                    double transmission_time = packet.size * 8 / DATA_RATE; // Transmission time in seconds
                    current_time += transmission_time;
                    total_throughput += packet.size; // Update throughput
                    double latency = current_time - packet.arrival_time;
                    latencies.push_back(latency);

                    // Remove the transmitted packet
                    user.packets.pop();
                }
            }

            if (all_done) break; // Exit loop if all packets are transmitted
        }
    }

    // Prints simulation results
    void printResults(int num_users) {
        double average_latency = std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
        double max_latency = *std::max_element(latencies.begin(), latencies.end());
        double throughput = total_throughput / current_time; // Throughput in bytes per second

        std::cout << CYAN << "WiFi 4 Simulation with " << num_users << " users:" << RESET << "\n";
        std::cout << GREEN << "Throughput: " << throughput / 1e6 << " MB/s" << RESET << "\n";
        std::cout << YELLOW << "Average Latency: " << average_latency << " seconds" << RESET << "\n";
        std::cout << MAGENTA << "Maximum Latency: " << max_latency << " seconds" << RESET << "\n";
        std::cout << BLUE << "Total Simulation Time: " << current_time << " seconds" << RESET << "\n\n";
    }
};

int main() {
    std::srand(time(0)); // Seed for random backoff times

    std::cout << CYAN << "WiFi 4 Simulation Results:" << RESET << "\n";
    std::cout << "---------------------------------------------\n";

    // Case 1: 1 user and 1 AP
    {
        std::vector<User> users;
        users.emplace_back(0); // Single user
        users[0].generatePackets(10, 0.0); // Generate packets

        AccessPoint ap;
        ap.simulate(users);
        ap.printResults(1);
    }

    // Case 2: 10 users and 1 AP
    {
        std::vector<User> users;
        for (int i = 0; i < 10; ++i) {
            users.emplace_back(i); // Create 10 users
            users[i].generatePackets(10, 0.0); // Generate packets
        }

        AccessPoint ap;
        ap.simulate(users);
        ap.printResults(10);
    }

    // Case 3: 100 users and 1 AP
    {
        std::vector<User> users;
        for (int i = 0; i < 100; ++i) {
            users.emplace_back(i); // Create 100 users
            users[i].generatePackets(10, 0.0); // Generate packets
        }

        AccessPoint ap;
        ap.simulate(users);
        ap.printResults(100);
    }

    return 0;
}
