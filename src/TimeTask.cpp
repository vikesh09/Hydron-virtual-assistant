#include "TimeTask.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

TimeTask::TimeTask() : Task("Time & Date Task") {}

void TimeTask::execute() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* timeInfo = std::localtime(&currentTime);

    std::cout << "[Hydron] Current Date and Time: " 
              << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S (%A)") 
              << std::endl;
}
