
#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <queue>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm> // For max_element

// Constants
extern const int PACKET_SIZE;           // Packet size in bytes (1 KB)
extern const double BANDWIDTH;         // Total bandwidth in Hz (20 MHz)
extern const double MODULATION_RATE;   // Bits per Hz (256-QAM)
extern const double CODING_RATE;       // Coding rate (5/6)
extern const double TOTAL_DATA_RATE;   // Total bits per second
extern const double TRANSMISSION_TIME; // 5 ms of parallel transmission time
extern const std::array<int, 3> SUB_CHANNELS; // Sub-channel widths in MHz

#endif // INCLUDES_H
