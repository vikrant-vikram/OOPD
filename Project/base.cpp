#include "includes.h"  // Include constants and macros
// #include "base.cpp"    // Include Packet and User classes
#include "constants.h"
// Packet class
class Packet {
public:
    int size;              // Size in bytes
    double arrival_time;   // Time the packet is ready for transmission

    // Constructor
    Packet(int size, double arrival_time) : size(size), arrival_time(arrival_time) {}
};

// User class
class User {
public:
    int id;                     // User ID
    std::queue<Packet> packets; // Queue of packets to be transmitted

    // Constructor
    User(int id) : id(id) {}

    // Method to generate packets for the user
    void generatePackets(int num_packets, double start_time) {
        for (int i = 0; i < num_packets; i++) {
            packets.push(Packet(PACKET_SIZE, start_time + i * 0.001)); // 1 ms interval
        }
    }
};


class Frequency {
private:
    double total_bandwidth;   // Total bandwidth (in Hz)
    double sub_channel_width; // Sub-channel width (in Hz)

public:
    Frequency(double bandwidth = BANDWIDTH, double sub_channel_width = 1e6)
        : total_bandwidth(bandwidth), sub_channel_width(sub_channel_width) {}

    // Calculate number of sub-channels
    int calculateSubChannels() const {
        return static_cast<int>(total_bandwidth / sub_channel_width);
    }

    // Calculate the data rate per sub-channel (considering efficiency factor)
    double getSubChannelRate(double total_data_rate) const {
        int sub_channel_count = calculateSubChannels();
        double sub_channel_rate = (total_data_rate / sub_channel_count) * 0.8; // Efficiency factor
        return sub_channel_rate;
    }

    // Setters
    void setSubChannelWidth(double width) {
        sub_channel_width = width;
    }

    void setTotalBandwidth(double bandwidth) {
        total_bandwidth = bandwidth;
    }

    // Getters
    double getSubChannelWidth() const {
        return sub_channel_width;
    }

    double getTotalBandwidth() const {
        return total_bandwidth;
    }

    // Print frequency details
    void printFrequencyInfo() const {
        int sub_channel_count = calculateSubChannels();
        std::cout << GREEN << "Frequency Configuration:\n" << RESET
                  << "  Total Bandwidth: " << total_bandwidth / 1e6 << " MHz\n"
                  << "  Sub-channel Width: " << sub_channel_width / 1e6 << " MHz\n"
                  << "  Number of Sub-channels: " << sub_channel_count << "\n";
    }
};
