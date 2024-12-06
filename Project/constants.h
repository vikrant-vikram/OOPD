// constants.h

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Packet size (1 KB)
const int PACKET_SIZE = 1024;

// Bandwidth (20 MHz)
const double BANDWIDTH = 20e6;

// Modulation rate (256-QAM)
const double MODULATION_RATE = 8.0;

// Coding rate (5/6)
const double CODING_RATE = 5.0 / 6.0;

// Total data rate (in bits per second)
const double TOTAL_DATA_RATE = BANDWIDTH * MODULATION_RATE * CODING_RATE;

// Transmission time (5 ms for parallel transmission)
const double TRANSMISSION_TIME = 0.005;

// Sub-channel widths (in MHz)
const std::array<int, 3> SUB_CHANNELS = {2, 4, 10}; // Sub-channel widths in MHz

// Colors for terminal output
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
       // Packet size in bytes (1 KB)
const int CSI_PACKET_SIZE = 200;     // Channel State Information (CSI) packet size in bytes
const int MAX_BACKOFF_TIME = 10;    // Max backoff time in microseconds

const double DATA_RATE = BANDWIDTH * MODULATION_RATE * CODING_RATE; // Bits per second
const double PARALLEL_TIME = 0.015;  // Parallel communication time in seconds (15 ms)
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
std::mutex simulation_mutex;

#endif // CONSTANTS_H
