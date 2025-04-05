#pragma once
#include "types.h"
#include "sensor_fusion.h"

#include <vector>
#include <mutex>

class Perception 
{
public:
    void run(SensorFusion* fusion);  // takes pointer to sensor module
    std::vector<Threat> getThreats();

private:
    std::vector<Threat> threats;
    std::mutex mtx;

    ThreatLevel assessThreat(const Obstacle& obs);
};
