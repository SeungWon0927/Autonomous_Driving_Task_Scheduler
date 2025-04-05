#pragma once
#include "types.h"
#include "perception.h"

#include <mutex>

class Planning
{
public:
    void run(Perception* perception);
    PathDecision getLatestDecision();

private:
    std::mutex mtx;
    PathDecision currentDecision;

    PathDecision computePath(const std::vector<Threat>& threats);
};
