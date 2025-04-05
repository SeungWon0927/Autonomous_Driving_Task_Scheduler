#include "dashboard.h"
#include "utils.h"

#include <thread>
#include <chrono>
#include <iomanip>
#include <iostream>

void Dashboard::run(
    SensorFusion* fusion,
    Perception* perception,
    Planning* planning,
    Control* control
)
{
    while (true)
    {
        // Fetch data from each module
        auto obs = fusion->getFusedObstacles();
        auto threats = perception->getThreats();
        auto decision = planning->getLatestDecision();
        auto command = control->getLatestCommand();

        // Clear screen
        std::cout << "\033[2J\033[1;1H";

        // Header
        std::cout << COLOR_CYAN
                  << "==================[ AD TASK SCHEDULER DASHBOARD ]=================="
                  << COLOR_RESET << "\n";

        // Sensor Fusion
        std::cout << COLOR_BLUE << "[Sensor Fusion]  Obstacle Count: " << obs.size() << COLOR_RESET << "\n";
        for (const auto& o : obs)
        {
            std::cout << "   ID:" << o.id << ", Dist: " << o.distance << "m"
                      << ", Angle: " << o.angle << "°, Source: " << o.source << "\n";
        }

        // Perception
        std::cout << COLOR_YELLOW << "[Perception]     Threats:\n" << COLOR_RESET;
        for (const auto& t : threats)
        {
            std::string levelStr = (t.level == HIGH ? "HIGH" : t.level == MEDIUM ? "MEDIUM" : "LOW");
            std::string color = (t.level == HIGH ? COLOR_RED :
                                t.level == MEDIUM ? COLOR_YELLOW : COLOR_GREEN);
            std::cout << "   -> " << "ID:" << t.obs.id << ", " << t.obs.distance
                      << "m @ " << t.obs.angle << "°, "
                      << "Level: " << color << levelStr << COLOR_RESET << "\n";
        }

        // Planning
        std::cout << COLOR_GREEN << "[Planning]       Direction: " << decision.direction
                  << ", Speed: " << decision.targetSpeed
                  << " m/s, Threat Level: " << (decision.threatLevel == HIGH ? "HIGH" :
                                                 decision.threatLevel == MEDIUM ? "MEDIUM" : "LOW")
                  << COLOR_RESET << "\n";

        // Control
        std::cout << COLOR_MAGENTA << "[Control]        Throttle: " << command.throttle
                  << ", Steering: " << command.steering << COLOR_RESET << "\n";

        std::cout << COLOR_CYAN
                  << "==================================================================="
                  << COLOR_RESET << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
