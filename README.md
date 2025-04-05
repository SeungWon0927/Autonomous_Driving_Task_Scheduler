# Multithreaded Autonomous Driving Task Scheduler

This project simulates a modular, real-time task scheduler for autonomous driving (AD) using C++17 and multithreading.  
It's designed as a **portfolio-grade project** to demonstrate systems integration, real-time logic, and autonomous behavior simulation.

![ADScheduler](https://github.com/user-attachments/assets/5ca02681-4d7e-4b0f-a64c-f823d466298f)


---

# Why This Project?

This project was designed to showcase:
- Systems-level thinking for real-time robotics
- Safe multithreaded programming with shared data coordination
- AD-style planning and control modules
- Real-time simulation without any hardware dependencies

---

## Overview

The simulation consists of five major modules, each running in its own thread:

| Module           | Purpose                                                                    |
|------------------|----------------------------------------------------------------------------|
| `Sensor Fusion`  | Simulates Lidar & Camera input and fuses them into a unified obstacle list |
| `Perception`     | Analyzes threat level based on obstacle data (distance, angle, velocity)   |
| `Planning`       | Determines safe path direction and target speed                            |
| `Control`        | Converts path decisions into throttle and steering commands                |
| `Dashboard`      | Displays real-time system state via a colorized ASCII dashboard            |

---


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


## 🧱 Folder Structure

```text
ad_task_scheduler_advanced/
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
```
---

## Build & Run Instructions

### ✅ Prerequisites

- C++17 or later
- CMake ≥ 3.10
- Linux, macOS, or WSL (tested in Ubuntu WSL2)



### Build 

```bash
cd build
cmake ..
make
```



### Run

```./ad_scheduler```

You’ll see a live-updating, colorized ASCII dashboard showing the simulation in real time.



### CSV Logging

Two CSV logs are generated in the current working directory:

```control_log.csv``` – throttle and steering values per cycle

```planning_log.csv``` – path direction, speed, and threat level per cycle

These can be analyzed using Excel, Python, or MATLAB.

---

# Author

**Seung Won Kim**

Feel free to connect on LinkedIn (https://www.linkedin.com/in/swk9270)
