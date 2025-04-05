#pragma once
#include "types.h"
#include <vector>
#include <mutex>

class SensorFusion 
{
public:
    void run(); // to launch in thread
    std::vector<Obstacle> getFusedObstacles();

private:
    std::vector<Obstacle> fusedObstacles;
    std::mutex mtx;

    void simulateSensors();
    std::vector<Obstacle> simulateLidar();
    std::vector<Obstacle> simulateCamera();
    std::vector<Obstacle> fuse(const std::vector<Obstacle>& lidar, const std::vector<Obstacle>& camera);
};
