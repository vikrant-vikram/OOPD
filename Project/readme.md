# WiFi Simulation Projects ![WiFi Logo](https://img.icons8.com/ios-filled/50/000000/wifi.png)

Welcome to the **WiFi Simulation Projects** repository! 🚀 This project simulates the performance of WiFi networks, specifically **WiFi 4**, **WiFi 5**, and **WiFi 6**, using various communication protocols and advanced features like **CSI**, **OFDMA**, and **backoff mechanisms**. The simulations are written in **C++** and provide detailed results on key performance metrics, such as **throughput**, **latency**, and **total simulation time**.

---

## 🧑‍💻 Project Overview

This repository contains three different WiFi simulation models:

| WiFi Standard | Description |
| ------------- | ----------- |
| **WiFi 4**    | Simulates basic packet transmission and calculates throughput. |
| **WiFi 5**    | Implements enhanced packet scheduling and parallel communication with CSI packet exchanges. |
| **WiFi 6**    | Utilizes **Orthogonal Frequency Division Multiple Access (OFDMA)**, allowing simultaneous communication through sub-channel management. |

Each simulation evaluates the system’s performance with varying user counts and sub-channel widths (for WiFi 6).

---

## ⚙️ Features

### **WiFi 4 Simulation**
- Basic packet transmission and throughput calculation.
- Simple model to simulate performance for a small number of users.

### **WiFi 5 Simulation**
- Enhanced scheduling with **CSI packet exchanges**.
- **Parallel communication** for efficient data transfer.

### **WiFi 6 Simulation**
- **OFDMA**: Users are allocated different sub-channels for simultaneous communication.
- Testing performance impact with varying **sub-channel widths** (e.g., 20 MHz, 40 MHz, 80 MHz).

### **Performance Metrics**
- **Throughput**: Total data successfully transmitted.
- **Average Latency**: Average time taken for packets to be transmitted.
- **Maximum Latency**: Maximum delay observed during the simulation.
- **Total Simulation Time**: Overall time taken to complete the simulation.

---

## 🚀 Getting Started

Follow these steps to set up your development environment and run the simulations.

### 🛠️ Prerequisites

Ensure you have the following installed:
- **C++ Compiler**: A **C++17** compatible compiler (e.g., `g++` or `clang++`).
- **Make**: A build tool (e.g., **GNU Make**) to compile and link the source code.

### 📥 Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/wifi-simulations.git
   cd wifi-simulations
Build the Project: Compile the project using Make:
make
Run the Simulations: After building, you can run the simulations:
WiFi 4:
./wifi4
WiFi 5:
./wifi5
WiFi 6:
./wifi6
Clean the Build: To clean up the object files and binaries:
make clean

## 🗂️ **Directory Structure**

Here’s an overview of the directory structure in this repository:

wifi-simulations/ │ ├── base.cpp # Common logic for users, packets, and basic transmission ├── constants.cpp # Definitions of constants (e.g., DATA_RATE, PACKET_SIZE) ├── includes.h # Header file for commonly used constants and declarations ├── problem1.cpp # WiFi 4 simulation code ├── problem2.cpp # WiFi 5 simulation code ├── problem3.cpp # WiFi 6 simulation code ├── Makefile # Build instructions └── README.md # This file
# This file
📊 Simulation Results

WiFi 4 Simulation:
Throughput: Evaluates throughput with different user counts (1, 10, 100 users).
Latency: Measures both average and maximum latency during the simulation.
WiFi 5 Simulation:
CSI Packet Exchange: Users sequentially exchange CSI packets.
Parallel Communication: Simulates up to 15ms of parallel communication.
WiFi 6 Simulation:
OFDMA: Users are assigned distinct sub-channels for simultaneous communication.
Sub-Channel Widths: Varying sub-channel widths (20 MHz, 40 MHz, 80 MHz) are tested.
📌 Example Output

Here’s an example of the results you will get after running any of the simulations:

WiFi 4 Simulation with 1 user:
- Throughput: 3.25 MB/s
- Average Latency: 0.021 seconds
- Maximum Latency: 0.035 seconds
- Total Simulation Time: 1.25 seconds
This result will be printed for each simulation scenario (1 user, 10 users, 100 users), allowing you to compare performance across different network conditions.
