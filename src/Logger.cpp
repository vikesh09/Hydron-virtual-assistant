#include "Logger.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

Logger::Logger(std::string filePath) : logFilePath(std::move(filePath)) {}

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* timeInfo = std::localtime(&currentTime);

    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}

void Logger::logCommand(const std::string& command) {
    if (command.empty()) return;

    std::ofstream outFile(logFilePath, std::ios::app);
    if (outFile.is_open()) {
        outFile << "[" << getCurrentTimestamp() << "] " << command << "\n";
        outFile.close();
    } else {
        std::cerr << "[Hydron Error] Unable to open log file for writing: " << logFilePath << std::endl;
    }
}

void Logger::printHistory() const {
    std::ifstream inFile(logFilePath);
    if (!inFile.is_open()) {
        std::cout << "[Hydron] No command history found (" << logFilePath << " does not exist yet)." << std::endl;
        return;
    }

    std::cout << "\n========== COMMAND HISTORY ==========" << std::endl;
    std::string line;
    int lineNum = 1;
    while (std::getline(inFile, line)) {
        std::cout << lineNum++ << ". " << line << std::endl;
    }
    std::cout << "=====================================\n" << std::endl;
    inFile.close();
}
