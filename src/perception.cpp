#include "perception.h"
#include "utils.h"
#include <thread>
#include <chrono>
#include <cmath>

void Perception::run(SensorFusion* fusion) 
{
    while (true) 
    {
        std::vector<Obstacle> obstacles = fusion->getFusedObstacles();
        std::vector<Threat> newThreats;

        for (const auto& obs : obstacles) 
        {
            ThreatLevel level = assessThreat(obs);
            newThreats.push_back({obs, level});
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            threats = newThreats;
        }

        log("Perception", "Updated threat levels for " + std::to_string(newThreats.size()) + " obstacle(s)", COLOR_YELLOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

ThreatLevel Perception::assessThreat(const Obstacle& obs) 
{
    if (obs.distance < 10 && std::abs(obs.angle) < 15) 
    {
        return HIGH;
    } 
    else if (obs.distance < 20 && std::abs(obs.angle) < 45) 
    {
        return MEDIUM;
    } 
    else 
    {
        return LOW;
    }
}

std::vector<Threat> Perception::getThreats() 
{
    std::lock_guard<std::mutex> lock(mtx);
    return threats;
}
