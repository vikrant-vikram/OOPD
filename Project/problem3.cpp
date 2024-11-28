// main.cpp
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

    // Simulates WiFi 6 communication with OFDMA
    void simulate(std::vector<User>& users, int sub_channel_width) {
        int sub_channel_count = BANDWIDTH / (sub_channel_width * 1e6); // Calculate number of sub-channels
        double sub_channel_rate = TOTAL_DATA_RATE / sub_channel_count; // Data rate per sub-channel

        while (true) {
            bool all_done = true;

            // Parallel transmission phase (5 ms)
            double parallel_end_time = current_time + TRANSMISSION_TIME;

            for (size_t i = 0; i < users.size(); i++) {
                User& user = users[i % users.size()]; // Round-robin scheduling

                for (int j = 0; j < sub_channel_count; j++) {
                    if (!user.packets.empty()) {
                        all_done = false;

                        Packet packet = user.packets.front();

                        // Ensure the current time aligns with packet arrival
                        if (current_time < packet.arrival_time) {
                            current_time = packet.arrival_time;
                        }

                        // Transmit the packet
                        double transmission_time = packet.size * 8 / sub_channel_rate;
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
            }

            current_time = parallel_end_time; // Move to the end of the parallel phase

            if (all_done) break; // Exit if all packets are transmitted
        }
    }

    // Returns simulation results as a string for easy logging with colors
    std::string getResults(int num_users, int sub_channel_width) {
        double average_latency = std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
        double max_latency = *std::max_element(latencies.begin(), latencies.end());
        double throughput = total_throughput / current_time; // Throughput in bytes per second

        std::ostringstream oss;
        oss << CYAN << "WiFi 6 Simulation with " << num_users << " users and "
            << sub_channel_width << " MHz sub-channels:\n" << RESET
            << GREEN << "Throughput: " << throughput / 1e6 << " MB/s\n" << RESET
            << YELLOW << "Average Latency: " << average_latency << " seconds\n" << RESET
            << MAGENTA << "Maximum Latency: " << max_latency << " seconds\n" << RESET
            << BLUE << "Total Simulation Time: " << current_time << " seconds\n" << RESET;
        return oss.str();
    }
};

// Main function
int main() {
    std::srand(time(0)); // Seed for randomness (if needed)

    std::cout << CYAN << "WiFi 6 Simulation Results:" << RESET << "\n";
    std::cout << "---------------------------------------------\n";

    // Store results
    std::ostringstream log_output;

    // Simulation cases
    for (int sub_channel_width : SUB_CHANNELS) {
        // Case 1: 1 user and 1 AP
        {
            std::vector<User> users;
            users.emplace_back(0); // Single user
            users[0].generatePackets(10, 0.0); // Generate packets

            AccessPoint ap;
            ap.simulate(users, sub_channel_width);
            log_output << ap.getResults(1, sub_channel_width);
        }

        // Case 2: 10 users and 1 AP
        {
            std::vector<User> users;
            for (int i = 0; i < 10; ++i) {
                users.emplace_back(i); // Create 10 users
                users[i].generatePackets(10, 0.0); // Generate packets
            }

            AccessPoint ap;
            ap.simulate(users, sub_channel_width);
            log_output << ap.getResults(10, sub_channel_width);
        }

        // Case 3: 100 users and 1 AP
        {
            std::vector<User> users;
            for (int i = 0; i < 100; ++i) {
                users.emplace_back(i); // Create 100 users
                users[i].generatePackets(10, 0.0); // Generate packets
            }

            AccessPoint ap;
            ap.simulate(users, sub_channel_width);
            log_output << ap.getResults(100, sub_channel_width);
        }
    }

    // Output all results at once
    std::cout << log_output.str();

    return 0;
}
