#include "control.h"
#include "utils.h"

#include <thread>
#include <chrono>

void Control::run(Planning* planning)
{
    log_to_csv("control_log.csv", "throttle,steering");
    while (true)
    {
        PathDecision decision = planning->getLatestDecision();
        ControlCommand cmd = computeCommand(decision);

        {
            std::lock_guard<std::mutex> lock(mtx);
            currentCommand = cmd;
        }

        log("Control", "Throttle: " + std::to_string(cmd.throttle) +
                      ", Steering: " + std::to_string(cmd.steering), COLOR_MAGENTA);
        
        // CSV Logging
        std::string csvLine = std::to_string(cmd.throttle) + "," +
        std::to_string(cmd.steering);
        log_to_csv("control_log.csv", csvLine);              

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

ControlCommand Control::computeCommand(const PathDecision& decision)
{
    ControlCommand cmd;

    // Throttle logic: linear scale (targetSpeed / maxSpeed)
    double maxSpeed = 20.0;
    cmd.throttle = std::min(1.0, decision.targetSpeed / maxSpeed);

    // Steering logic: mapped from direction
    if (decision.direction == "Left")
    {
        cmd.steering = -0.5;
    }
    else if (decision.direction == "Right")
    {
        cmd.steering = 0.5;
    }
    else // Straight
    {
        cmd.steering = 0.0;
    }

    return cmd;
}

ControlCommand Control::getLatestCommand()
{
    std::lock_guard<std::mutex> lock(mtx);
    return currentCommand;
}
