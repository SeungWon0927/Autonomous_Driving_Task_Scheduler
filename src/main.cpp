#include "sensor_fusion.h"
#include "perception.h"
#include "planning.h"
#include "control.h"
#include "dashboard.h"

#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    std::cout << "Starting Multithreaded AD Task Scheduler (Advanced Edition)..." << std::endl;

    // Instantiate all modules
    SensorFusion fusion;
    Perception perception;
    Planning planning;
    Control control;
    Dashboard dashboard;

    // Launch threads
    std::thread t1(&SensorFusion::run, &fusion);
    std::thread t2(&Perception::run, &perception, &fusion);
    std::thread t3(&Planning::run, &planning, &perception);
    std::thread t4(&Control::run, &control, &planning);
    std::thread t5(&Dashboard::run, &dashboard, &fusion, &perception, &planning, &control);

    // Wait for all threads to finish (they never will in this case)
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
