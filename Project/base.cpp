// base.cpp

#include "includes.h"  // Make sure this includes necessary headers

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
