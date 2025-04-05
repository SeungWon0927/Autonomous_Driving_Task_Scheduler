#pragma once
#include <string>
#include <vector>

enum ThreatLevel 
{
    LOW,
    MEDIUM,
    HIGH
};

struct Obstacle 
{
    int id;
    double distance;       // meters
    double angle;          // degrees (-90 = left, 0 = front, +90 = right)
    double rel_velocity;   // relative speed to vehicle (m/s)
    std::string source;    // "Lidar", "Camera", or "Fused"
};

struct Threat 
{
    Obstacle obs;
    ThreatLevel level;
};

struct PathDecision 
{
    std::string direction;     // "Straight", "Left", "Right", etc.
    double targetSpeed;        // m/s
    ThreatLevel threatLevel;
};

struct ControlCommand 
{
    double throttle;           // 0.0 to 1.0
    double steering;           // -1.0 (left) to 1.0 (right)
};
