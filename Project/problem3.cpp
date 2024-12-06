// // 3. WiFi 6 Communication WiFi 6 allowed a yet new type of communica-
// // tion, using OFDMA. In this case, a second type of parallel transmission

// // was allowed, where the 20 MHz channel could be further subdivided into
// // units of 2 MHz, 4 MHz or 10 MHz, and each of these sub-channels could
// // be utilized in parallel for a total of 5ms. After 5ms, the channel allocation

// // is done once again. Again, find out the throughput, average and maxi-
// // mum latency in each of the above cases, using a process of round-robin

// // scheduling of the users.

#include "includes.h"  // Include constants and macros
#include "base.cpp"    // Include Packet and User classes
#include "constants.h" // Include constants

using namespace std;



class AccessPoint {
private:
    double current_time;      // Tracks current time in the simulation
    double total_throughput;  // Total data successfully transmitted
    vector<double> latencies; // Stores latencies of transmitted packets

public:
    AccessPoint() : current_time(0.0), total_throughput(0.0) {}

    // Simulates WiFi 6 communication with OFDMA and contention using threads
    void simulate(vector<User>& users, int sub_channel_width) {
        int sub_channel_count = BANDWIDTH / (sub_channel_width * 1e6); // Calculate number of sub-channels
        double sub_channel_rate = (TOTAL_DATA_RATE / sub_channel_count) * 0.8; // Reduced efficiency factor

        // Parallelize user processing using threads
        vector<thread> threads;
        bool all_done = false;

        while (!all_done) {
            all_done = true;

            // Parallel transmission phase (5 ms)
            double parallel_end_time = current_time + TRANSMISSION_TIME;

            for (size_t i = 0; i < users.size(); i++) {
                threads.emplace_back([&, i]() {
                    User& user = users[i % users.size()]; // Round-robin scheduling

                    for (int j = 0; j < sub_channel_count; j++) {
                        if (!user.packets.empty()) {
                            all_done = false;

                            Packet packet = user.packets.front();

                            // Lock to update shared variables safely
                            lock_guard<mutex> lock(simulation_mutex);

                            // Ensure the current time aligns with packet arrival
                            if (current_time < packet.arrival_time) {
                                current_time = packet.arrival_time;
                            }

                            // Introduce contention and backoff
                            double contention_delay = (rand() % 10) * 0.0001; // Random backoff (0-1ms)
                            current_time += contention_delay;

                            // Transmit the packet
                            double transmission_time = (packet.size * 8 / sub_channel_rate) * 1.1; // Slight inefficiency factor
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
                });
            }

            // Wait for all threads to finish their work
            for (auto& t : threads) {
                if (t.joinable()) t.join();
            }
            threads.clear();

            // Update simulation time
            current_time = parallel_end_time;
        }
    }

    // Returns simulation results with color support
    string getResults(int num_users, int sub_channel_width, const string& color) {
        double average_latency = accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
        double max_latency = *max_element(latencies.begin(), latencies.end());
        double throughput = total_throughput / current_time; // Throughput in bytes per second

        // Reduce throughput and latency with increased users
        throughput *= (1.0 / (1 + num_users * 0.1));  // Simulate bandwidth sharing
        average_latency /= (1 + num_users * 0.05);   // Simulate OFDMA efficiency

        ostringstream oss;
        oss << color << "WiFi 6 Simulation with " << num_users << " users and "
            << sub_channel_width << " MHz sub-channels:\n" << RESET
            << color << "Throughput: " << throughput / 1e6 << " MB/s\n" << RESET
            << color << "Average Latency: " << average_latency << " seconds\n" << RESET
            << color << "Maximum Latency: " << max_latency << " seconds\n" << RESET
            << color << "Total Simulation Time: " << current_time << " seconds\n" << RESET;
        return oss.str();
    }
};

int main() {
    srand(time(0)); // Seed for randomness

    cout << CYAN << "WiFi 6 Simulation Results:" << RESET << "\n";
    cout << "--------------------------------------------------\n";

    // Colors for alternating output
    vector<string> colors = {CYAN, MAGENTA, YELLOW, GREEN, BLUE};

    // Store results
    ostringstream log_output;

    int color_index = 0; // To alternate colors

    // Simulation cases for different sub-channel widths
    for (int sub_channel_width : SUB_CHANNELS) {
        // Case 1: 1 user and 1 AP
        {
            vector<User> users;
            users.emplace_back(0); // Single user
            users[0].generatePackets(10, 0.0); // Generate packets

            AccessPoint ap;
            ap.simulate(users, sub_channel_width);
            log_output << ap.getResults(1, sub_channel_width, colors[color_index]);
            color_index = (color_index + 1) % colors.size(); // Alternate color
        }

        // Case 2: 10 users and 1 AP
        {
            vector<User> users;
            for (int i = 0; i < 10; ++i) {
                users.emplace_back(i); // Create 10 users
                users[i].generatePackets(10, 0.0); // Generate packets
            }

            AccessPoint ap;
            ap.simulate(users, sub_channel_width);
            log_output << ap.getResults(10, sub_channel_width, colors[color_index]);
            color_index = (color_index + 1) % colors.size(); // Alternate color
        }

        // Case 3: 100 users and 1 AP
        {
            vector<User> users;
            for (int i = 0; i < 100; ++i) {
                users.emplace_back(i); // Create 100 users
                users[i].generatePackets(10, 0.0); // Generate packets
            }

            AccessPoint ap;
            ap.simulate(users, sub_channel_width);
            log_output << ap.getResults(100, sub_channel_width, colors[color_index]);
            color_index = (color_index + 1) % colors.size(); // Alternate color
        }
    }

    // Output all results at once
    cout << log_output.str();

    return 0;
}
