#pragma once
#include "types.h"
#include "planning.h"

#include <mutex>

class Control
{
public:
    void run(Planning* planning);
    ControlCommand getLatestCommand();

private:
    std::mutex mtx;
    ControlCommand currentCommand;

    ControlCommand computeCommand(const PathDecision& decision);
};
