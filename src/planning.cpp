#include "planning.h"
#include "utils.h"

#include <thread>
#include <chrono>
#include <cmath>

void Planning::run(Perception* perception)
{
    log_to_csv("planning_log.csv", "direction,target_speed,threat_level");
    while (true)
    {
        std::vector<Threat> threats = perception->getThreats();
        PathDecision decision = computePath(threats);

        {
            std::lock_guard<std::mutex> lock(mtx);
            currentDecision = decision;
        }

        log("Planning", "Direction: " + decision.direction + 
                        ", Speed: " + std::to_string(decision.targetSpeed) + 
                        " m/s", COLOR_GREEN);

        std::string csvLine = decision.direction + "," + std::to_string(decision.targetSpeed) + "," +
                        (decision.threatLevel == HIGH ? "HIGH" : decision.threatLevel == MEDIUM ? "MEDIUM" : "LOW");
        log_to_csv("planning_log.csv", csvLine);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

PathDecision Planning::computePath(const std::vector<Threat>& threats)
{
    PathDecision decision;
    decision.direction = "Straight";
    decision.targetSpeed = 15.0;
    decision.threatLevel = LOW;

    for (const auto& threat : threats)
    {
        if (threat.level == HIGH && std::abs(threat.obs.angle) < 20)
        {
            decision.direction = "Right";
            decision.targetSpeed = 5.0;
            decision.threatLevel = HIGH;
            return decision;
        }
        else if (threat.level == MEDIUM && std::abs(threat.obs.angle) < 45)
        {
            decision.direction = "Left";
            decision.targetSpeed = 10.0;
            decision.threatLevel = MEDIUM;
        }
    }

    return decision;
}

PathDecision Planning::getLatestDecision()
{
    std::lock_guard<std::mutex> lock(mtx);
    return currentDecision;
}
