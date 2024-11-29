// 2. WiFi 5 Communication WiFi 5 allowed a new type of communication,
// using multi-user MIMO. In this case, parallel transmission was allowed.
// However, parallel communication could be done only after (i) a single
// broadcast packet was sent by the access point, and (ii) each user would
// sequentially send their channel state information, which would be a single
// packet of 200 bytes. Once this was done, each user could communicate in
// parallel for a total of 15 ms. After 15 ms, the above process is repeated.
// Find out the throughput, average and maximum latency in each of the
// above cases once again, assuming round-robin scheduling of the users.

#include "includes.h"  // Include constants and macros
#include "base.cpp"    // Include Packet and User classes
#include "constants.h" // Include constants

using namespace std;

// Frequency Class to handle bandwidth and sub-channel configuration


class AccessPoint {
private:
    double current_time;      // Tracks current time in the simulation
    double total_throughput;  // Total data successfully transmitted
    vector<double> latencies; // Stores latencies of transmitted packets

public:
    AccessPoint() : current_time(0.0), total_throughput(0.0) {}

    // Simulates WiFi 5 communication
    void simulate(vector<User>& users, Frequency& frequency) {
        try {
            if (users.empty()) {
                throw runtime_error("No users provided for simulation.");
            }

            // Frequency rate
            double sub_channel_rate = frequency.getSubChannelRate(TOTAL_DATA_RATE);

            while (true) {
                bool all_done = true;

                // Step 1: Broadcast packet from AP
                current_time += CSI_PACKET_SIZE * 8 / sub_channel_rate;

                // Step 2: Each user sends CSI packet sequentially
                for (auto& user : users) {
                    current_time += CSI_PACKET_SIZE * 8 / sub_channel_rate;
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

                current_time = parallel_end_time; // Move to the end of parallel phase

                if (all_done) break; // Exit if all packets are transmitted
            }
        } catch (const exception& e) {
            cerr << RED << "Error during simulation: " << e.what() << RESET << endl;
        }
    }

    // Prints the results of the simulation with a specific color
    void printResults(int num_users, Frequency& frequency, const string& color) {
        try {
            if (latencies.empty()) {
                throw runtime_error("No data to display. Simulation might have failed.");
            }

            double average_latency = accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
            double max_latency = *max_element(latencies.begin(), latencies.end());
            double throughput = total_throughput / current_time; // Throughput in bytes per second

            cout << color << "WiFi 5 Simulation with " << num_users << " users:\n" << RESET;
            frequency.printFrequencyInfo(); // Show frequency configuration
            cout << color << "Throughput: " << throughput / 1e6 << " MB/s" << RESET << "\n";
            cout << color << "Average Latency: " << average_latency << " seconds" << RESET << "\n";
            cout << color << "Maximum Latency: " << max_latency << " seconds" << RESET << "\n";
            cout << color << "Total Simulation Time: " << current_time << " seconds\n" << RESET << "\n";
        } catch (const exception& e) {
            cerr << RED << "Error in displaying results: " << e.what() << RESET << endl;
        }
    }
};

int main() {
    srand(time(0)); // Seed random number generator

    cout << CYAN << "WiFi 5 Simulation Results:" << RESET << "\n";
    cout << "---------------------------------------------\n";

    // Fixed simulation configurations
    const int num_users = 10;      // Set the number of users
    const int num_packets = 10;    // Set the number of packets per user
    const int sub_channel_width = 40;  // Set sub-channel width (in MHz)

    // Frequency setup
    Frequency frequency(BANDWIDTH, sub_channel_width * 1e6); // Initialize Frequency

    // Case 1: 1 user and 1 AP
    {
        try {
            vector<User> users;
            for (int i = 0; i < num_users; ++i) {
                users.emplace_back(i); // Create users
                users[i].generatePackets(num_packets, 0.0); // Each generates specified number of packets
            }

            AccessPoint ap;
            ap.simulate(users, frequency);
            ap.printResults(num_users, frequency, CYAN);
        } catch (const exception& e) {
            cerr << RED << "Error in Case 1: " << e.what() << RESET << endl;
        }
    }

    // Case 2: 10 users and 1 AP (same as Case 1)
    {
        try {
            vector<User> users;
            for (int i = 0; i < num_users; ++i) {
                users.emplace_back(i); // Create users
                users[i].generatePackets(num_packets, 0.0); // Each generates specified number of packets
            }

            AccessPoint ap;
            ap.simulate(users, frequency);
            ap.printResults(num_users, frequency, MAGENTA);
        } catch (const exception& e) {
            cerr << RED << "Error in Case 2: " << e.what() << RESET << endl;
        }
    }

    // Case 3: 100 users and 1 AP (same as Case 1 but with different user count)
    {
        try {
            vector<User> users;
            for (int i = 0; i < 100; ++i) {
                users.emplace_back(i); // Create 100 users
                users[i].generatePackets(num_packets, 0.0); // Each generates specified number of packets
            }

            AccessPoint ap;
            ap.simulate(users, frequency);
            ap.printResults(100, frequency, YELLOW);
        } catch (const exception& e) {
            cerr << RED << "Error in Case 3: " << e.what() << RESET << endl;
        }
    }

    return 0;
}
