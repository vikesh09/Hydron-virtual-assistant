#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// Class responsible for command history logging and file I/O (Encapsulation & File Handling)
class Logger {
private:
    std::string logFilePath;

    // Helper method to get formatted timestamp
    static std::string getCurrentTimestamp();

public:
    explicit Logger(std::string filePath = "history.txt");

    // Appends command with timestamp to history file
    void logCommand(const std::string& command);

    // Reads and prints all logged commands
    void printHistory() const;
};

#endif // LOGGER_H
