
// 1. WiFi 4 Communication WiFi communication happens via a single ac-
// cess point and a set of users. A single transmission consists of sniffing of

// the channel, and transmission of the data packet if the channel is free. If
// the channel is not free, the transmission is deferred by a random unit of
// time (subject to a maximum limit of backoff time), followed by repetition
// of the above process. Simulate this above process of transmission to find
// out the throughput, average and maximum latency if a total of (i) 1 user
// and 1 AP is communicating, (ii) 10 users and 1 AP is communicating,
// and (iii) 100 users and 1 AP are communicating. You may assume that a
// total of 20 MHz being used as bandwidth, modulation of 256-QAM and
// coding rate of 5/6 is used for transmission and that each packet has size
// of 1 KB. You may ignore the other periods of time wastage such as DIFS,
// CIFS and guard intervals.



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

    // Validates users and packets
    void validateUsers(const vector<User>& users) {
        if (users.empty()) {
            throw runtime_error("No users provided for simulation.");
        }
        for (const auto& user : users) {
            if (user.packets.empty()) {
                throw runtime_error("User has no packets to transmit.");
            }
        }
    }

public:
    AccessPoint() : current_time(0.0), total_throughput(0.0) {}

    // Simulates the communication for a set of users
    void simulate(vector<User>& users, Frequency& frequency) {
        try {
            validateUsers(users); // Check for valid input

            double sub_channel_rate = frequency.getSubChannelRate(TOTAL_DATA_RATE);

            while (true) {
                bool all_done = true;

                for (auto& user : users) {
                    if (!user.packets.empty()) {
                        all_done = false;

                        Packet packet = user.packets.front();

                        // Ensure current time aligns with packet arrival
                        if (current_time < packet.arrival_time) {
                            current_time = packet.arrival_time;
                        }

                        // Transmission time with sub-channel rate
                        double transmission_time = (packet.size * 8) / sub_channel_rate;
                        current_time += transmission_time;

                        total_throughput += packet.size; // Update throughput

                        double latency = current_time - packet.arrival_time;
                        latencies.push_back(latency);

                        user.packets.pop(); // Remove the transmitted packet
                    }
                }

                if (all_done) break; // Exit if all packets are transmitted
            }
        } catch (const exception& e) {
            cerr << RED << "Error during simulation: " << e.what() << RESET << endl;
        }
    }

    // Prints the results of the simulation
    void printResults(int num_users, Frequency& frequency, const string& color) {
        try {
            if (latencies.empty()) {
                throw runtime_error("No data to display. Simulation might have failed.");
            }

            double average_latency = accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
            double max_latency = *max_element(latencies.begin(), latencies.end());
            double throughput = total_throughput / current_time; // Throughput in bytes per second

            cout << color << "WiFi Simulation with " << num_users << " users:\n" << RESET;
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

    cout << CYAN << "WiFi 4 Simulation Results:" << RESET << "\n";
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
            ap.printResults(100, frequency, CYAN);
        } catch (const exception& e) {
            cerr << RED << "Error in Case 3: " << e.what() << RESET << endl;
        }
    }

    return 0;
}
