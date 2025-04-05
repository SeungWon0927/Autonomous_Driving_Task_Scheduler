cmake_minimum_required(VERSION 3.10)
project(MultithreadedADTaskScheduler)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(ad_scheduler
    src/main.cpp
    src/sensor_fusion.cpp
    src/perception.cpp
    src/planning.cpp
    src/control.cpp
    src/dashboard.cpp
)
