# Multithreaded Autonomous Driving Task Scheduler

This project simulates a modular, real-time task scheduler for autonomous driving (AD) using C++17 and multithreading.  
It's designed as a **portfolio-grade project** to demonstrate systems integration, real-time logic, and autonomous behavior simulation.

## Overview

The simulation consists of five major modules, each running in its own thread:

| Module           | Purpose                                                                    |
|------------------|----------------------------------------------------------------------------|
| `Sensor Fusion`  | Simulates Lidar & Camera input and fuses them into a unified obstacle list |
| `Perception`     | Analyzes threat level based on obstacle data (distance, angle, velocity)   |
| `Planning`       | Determines safe path direction and target speed                            |
| `Control`        | Converts path decisions into throttle and steering commands                |
| `Dashboard`      | Displays real-time system state via a colorized ASCII dashboard            |


## ✨ Features

- ✅ Multithreaded architecture using `std::thread`, `mutex`, and `condition_variable`
- ✅ Terminal-based live dashboard with ANSI color output
- ✅ Simulated Lidar & Camera sensor data
- ✅ Sensor fusion with basic data association
- ✅ Threat classification (LOW / MEDIUM / HIGH)
- ✅ Rule-based path planning
- ✅ PID-style throttle and steering generation
- ✅ CSV logging for later analysis (`control_log.csv`, `planning_log.csv`)
- ✅ Lightweight, cross-platform (runs on WSL, Linux, or native POSIX)

---

## Folder Structure

ad_task_scheduler/
├── build/                      # Build artifacts (created by CMake)
├── CMakeLists.txt              # Build configuration
├── README.md                   # Project documentation
└── src/
    ├── main.cpp                # Main thread to orchestrate modules
    ├── sensor_fusion.h/.cpp    # Lidar + Camera fusion logic
    ├── perception.h/.cpp       # Threat analysis from fused sensor data
    ├── planning.h/.cpp         # Path planning based on threat level
    ├── control.h/.cpp          # Control command generation (steering/throttle)
    ├── dashboard.h/.cpp        # ASCII dashboard displaying system state
    ├── types.h                 # Shared data types (obstacles, commands, etc.)
    └── utils.h                 # Logging and terminal formatting helpers


## Build & Run Instructions

### ✅ Prerequisites

- C++17 or later
- CMake ≥ 3.10
- Linux, macOS, or WSL (tested in Ubuntu WSL2)

### 🔧 Build & Run

```bash
cd build
cmake ..
make
./ad_scheduler