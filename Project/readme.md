# WiFi Simulation Projects

Welcome to the **WiFi Simulation Projects** repository! This collection contains simulations for **WiFi 4**, **WiFi 5**, and **WiFi 6**, using various communication protocols and advanced features like **CSI**, **OFDMA**, and **backoff mechanisms**. The simulations are written in **C++** and provide detailed results on key performance metrics, such as throughput, latency, and total simulation time.

---

## Project Overview

This repository features three different WiFi simulation models that simulate network performance under different WiFi standards:

### 1. **WiFi 4 Simulation**
- Simulates basic packet transmission and calculates throughput for WiFi 4.
- Provides insights into how WiFi 4 behaves with a fixed number of users.

### 2. **WiFi 5 Simulation**
- Implements enhanced packet scheduling and parallel communication.
- Simulates CSI packet exchanges and parallel transmission for up to 15 ms.

### 3. **WiFi 6 Simulation**
- Utilizes **Orthogonal Frequency Division Multiple Access (OFDMA)** for simultaneous communication.
- Users are assigned different sub-channels, and performance is tested with varying sub-channel widths.

Each simulation adjusts parameters like the number of users and sub-channel width (WiFi 6) to evaluate performance under different conditions.

---

## Features

- **WiFi 4 Simulation**: Basic packet transmission, throughput, and latency calculation.
- **WiFi 5 Simulation**: Parallel communication, CSI packet exchange, and enhanced scheduling.
- **WiFi 6 Simulation**: OFDMA-based scheduling, sub-channel management, and width adjustment.
- **Performance Metrics**: Throughput, average latency, maximum latency, and total simulation time.

---

## Getting Started

To get started with the WiFi simulation projects, follow these steps to set up your development environment.

### Prerequisites

Before running the simulations, ensure that you have the following:

- **C++ Compiler**: A C++17 compatible compiler (e.g., `g++` or `clang++`).
- **Make**: A build tool (e.g., **GNU Make**) to compile and link the source code.

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

The project follows a simple directory structure:

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

Here are the results you can expect from the simulations:

WiFi 4 Simulation:
Throughput: Simulates throughput performance with 1, 10, or 100 users.
Latency: Tracks the average and maximum latencies during the simulation.
WiFi 5 Simulation:
CSI Packet Exchange: Simulates the sequential sending of CSI packets by users.
Parallel Communication: Up to 15 ms of parallel communication is simulated.
WiFi 6 Simulation:
OFDMA: Users are assigned different sub-channels for simultaneous transmission.
Sub-Channel Width: Different sub-channel widths (20 MHz, 40 MHz, 80 MHz) are tested for performance impact.
Example Output

When running the simulations, you will receive detailed results for each scenario, like:

WiFi 4 Simulation with 1 user:
- Throughput: 3.25 MB/s
- Average Latency: 0.021 seconds
- Maximum Latency: 0.035 seconds
- Total Simulation Time: 1.25 seconds
You can experiment with different user counts (e.g., 1, 10, 100) and observe how throughput and latency are affected.
