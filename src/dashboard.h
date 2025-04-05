#pragma once

#include "sensor_fusion.h"
#include "perception.h"
#include "planning.h"
#include "control.h"

class Dashboard
{
public:
    void run(
        SensorFusion* fusion,
        Perception* perception,
        Planning* planning,
        Control* control
    );
};
