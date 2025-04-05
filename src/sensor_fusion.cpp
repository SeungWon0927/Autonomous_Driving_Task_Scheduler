#include "sensor_fusion.h"
#include "utils.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <random>

void SensorFusion::run() 
{
    while (true) {
        simulateSensors();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void SensorFusion::simulateSensors() 
{
    auto lidar = simulateLidar();
    auto camera = simulateCamera();
    auto fused = fuse(lidar, camera);

    {
        std::lock_guard<std::mutex> lock(mtx);
        fusedObstacles = fused;
    }

    log("SensorFusion", "Fused " + std::to_string(fused.size()) + " obstacle(s)", COLOR_BLUE);
}

std::vector<Obstacle> SensorFusion::simulateLidar() 
{
    std::vector<Obstacle> lidar;
    int num = rand() % 3 + 1;
    for (int i = 0; i < num; ++i) 
    {
        lidar.push_back({
            i,
            10 + rand() % 30,          // distance 10–40m
            (rand() % 120 - 60),       // angle -60 to +60°
            (rand() % 10 - 5) * 0.5,   // rel velocity -2.5 to +2.5
            "Lidar"
        });
    }
    return lidar;
}

std::vector<Obstacle> SensorFusion::simulateCamera() 
{
    std::vector<Obstacle> camera;
    int num = rand() % 3 + 1;
    for (int i = 0; i < num; ++i) {
        camera.push_back({
            i + 10,
            0,                          // no distance (Camera can't measure)
            (rand() % 120 - 60),        // angle -60 to +60°
            0,
            "Camera"
        });
    }
    return camera;
}

std::vector<Obstacle> SensorFusion::fuse(const std::vector<Obstacle>& lidar, const std::vector<Obstacle>& camera) 
{
    std::vector<Obstacle> result;

    for (const auto& l : lidar) 
    {
        Obstacle fused = l;

        for (const auto& c : camera) 
        {
            if (std::abs(l.angle - c.angle) < 10.0) 
            {
                fused.angle = (l.angle + c.angle) / 2.0;
                fused.source = "Fused";
                break;
            }
        }

        result.push_back(fused);
    }

    return result;
}

std::vector<Obstacle> SensorFusion::getFusedObstacles() 
{
    std::lock_guard<std::mutex> lock(mtx);
    return fusedObstacles;
}
