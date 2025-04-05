#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

// Colors
#define COLOR_RESET  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE   "\033[34m"
#define COLOR_CYAN   "\033[36m"
#define COLOR_MAGENTA   "\033[38m"

inline void log(const std::string& module, const std::string& message, const std::string& color = COLOR_CYAN) 
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeStr = std::ctime(&now);
    timeStr.pop_back(); // remove newline
    std::cout << color << "[" << timeStr << "][" << module << "] " << message << COLOR_RESET << std::endl;
}

inline void log_to_csv(const std::string& filename, const std::string& line)
{
    static std::mutex fileMutex;
    std::lock_guard<std::mutex> lock(fileMutex);

    std::ofstream file;
    file.open(filename, std::ios::app); // append mode
    if (file.is_open())
    {
        file << line << "\n";
        file.close();
    }
}
