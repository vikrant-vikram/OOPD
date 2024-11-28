
#include "includes.h"  // Include the constants and necessary header files
#include "base.cpp"    // Include Packet and User class
#include "constants.h" // Include the constants header file

class AccessPoint {
private:
    double current_time;      // Tracks the current time in the simulation
    double total_throughput;  // Total data successfully transmitted
    std::vector<double> latencies; // Stores latencies of transmitted packets

public:
    AccessPoint() : current_time(0.0), total_throughput(0.0) {}

    // Simulates WiFi 5 communication
    void simulate(std::vector<User>& users) {
        while (true) {
            bool all_done = true;

            // Step 1: Broadcast packet from AP
            current_time += CSI_PACKET_SIZE * 8 / DATA_RATE;

            // Step 2: Each user sends CSI packet sequentially
            for (auto& user : users) {
                current_time += CSI_PACKET_SIZE * 8 / DATA_RATE;
            }

            // Step 3: Parallel communication for 15 ms
            double parallel_end_time = current_time + PARALLEL_TIME;

            for (auto& user : users) {
                while (!user.packets.empty()) {
                    all_done = false;

                    Packet packet = user.packets.front();

                    // Ensure the current time aligns with packet arrival
                    if (current_time < packet.arrival_time) {
                        current_time = packet.arrival_time;
                    }

                    // Transmit the packet during parallel communication
                    double transmission_time = packet.size * 8 / DATA_RATE;
                    if (current_time + transmission_time <= parallel_end_time) {
                        current_time += transmission_time;
                        total_throughput += packet.size;

                        // Record latency
                        double latency = current_time - packet.arrival_time;
                        latencies.push_back(latency);

                        // Remove packet after transmission
                        user.packets.pop();
                    } else {
                        break; // Parallel time exhausted for this cycle
                    }
                }
            }

            current_time = parallel_end_time; // Move to the end of parallel phase

            if (all_done) break; // Exit if all packets are transmitted
        }
    }

    // Prints simulation results with colors
    void printResults(int num_users) {
        double average_latency = std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
        double max_latency = *std::max_element(latencies.begin(), latencies.end());
        double throughput = total_throughput / current_time; // Throughput in bytes per second

        std::cout << CYAN << "WiFi 5 Simulation with " << num_users << " users:" << RESET << "\n";
        std::cout << GREEN << "Throughput: " << throughput / 1e6 << " MB/s" << RESET << "\n";
        std::cout << YELLOW << "Average Latency: " << average_latency << " seconds" << RESET << "\n";
        std::cout << MAGENTA << "Maximum Latency: " << max_latency << " seconds" << RESET << "\n";
        std::cout << BLUE << "Total Simulation Time: " << current_time << " seconds" << RESET << "\n\n";
    }
};

// Main function
int main() {
    std::srand(time(0)); // Seed for randomness (if needed)

    std::cout << CYAN << "WiFi 5 Simulation Results:" << RESET << "\n";
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
