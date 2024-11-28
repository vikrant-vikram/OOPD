# WiFi Simulation Projects

Welcome to the WiFi Simulation Projects repository! This collection includes simulations for WiFi 4, WiFi 5, and WiFi 6 using different communication protocols and features like CSI, OFDMA, and backoff mechanisms. The simulations are written in C++ and provide detailed results for throughput, latency, and other performance metrics.

## Project Overview

This repository contains three different WiFi simulation models:
- **WiFi 4 Simulation**: Simulates the behavior of WiFi 4 using basic packet transmission.
- **WiFi 5 Simulation**: Simulates WiFi 5 communication with enhanced packet scheduling and parallel communication.
- **WiFi 6 Simulation**: Simulates WiFi 6 communication with Orthogonal Frequency Division Multiple Access (OFDMA) and dynamic sub-channel usage.

Each simulation involves varying the number of users and adjusting parameters like sub-channel width for WiFi 6 to evaluate performance under different conditions.

## Features

- **WiFi 4 Simulation**: Basic packet transmission and throughput calculation.
- **WiFi 5 Simulation**: Parallel communication and sequential CSI packet exchange between users.
- **WiFi 6 Simulation**: OFDMA-based packet scheduling with different sub-channel widths.
- **Performance Metrics**: Throughput, average latency, maximum latency, and total simulation time.

## Getting Started

To get started with the WiFi simulation projects, follow these steps to set up your development environment.

### Prerequisites

- **C++ Compiler**: Requires a C++17 compatible compiler (e.g., `g++` or `clang++`).
- **Make**: A build tool (e.g., GNU Make) for compiling and linking the source code.

### Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/wifi-simulations.git
   cd wifi-simulations
Build the Project: To compile the project, run the following command:
make
Run the Simulations: After building the project, you can run each simulation as follows:
For WiFi 4:
./wifi4
For WiFi 5:
./wifi5
For WiFi 6:
./wifi6
Clean the Build: If you want to clean up the object files and the compiled binaries, use:
make clean
Directory Structure

wifi-simulations/
│
├── base.cpp          # Common logic for users, packets, and basic transmission
├── constants.cpp     # Definitions of constants (e.g., DATA_RATE, PACKET_SIZE)
├── includes.h        # Header file for commonly used constants and declarations
├── problem1.cpp      # WiFi 4 simulation code
├── problem2.cpp      # WiFi 5 simulation code
├── problem3.cpp      # WiFi 6 simulation code
├── Makefile          # Build instructions
└── README.md         # This file
Simulation Results

WiFi 4 Simulation:
Throughput: Simulates the throughput with a fixed number of users (1, 10, 100).
Latency: Tracks the average and maximum latencies during the simulation.
WiFi 5 Simulation:
CSI Packet Exchange: Each user sends a CSI packet sequentially.
Parallel Communication: Up to 15ms of parallel communication between users is simulated.
WiFi 6 Simulation:
OFDMA: Users are assigned different sub-channels for simultaneous transmission.
Sub-Channel Width: Different sub-channel widths (e.g., 20 MHz, 40 MHz, 80 MHz) are tested for their performance impact.
Example Output

Running any of the simulations will provide you with results like:

WiFi 4 Simulation with 1 users:
Throughput: 3.25 MB/s
Average Latency: 0.021 seconds
Maximum Latency: 0.035 seconds
Total Simulation Time: 1.25 seconds
Contributing



GitHub: @vikrant-vikram
