#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "CommandParser.h"
#include "Logger.h"
#include "Task.h"
#include <string>
#include <memory>

// Central Assistant Controller managing REPL loop and task execution (Encapsulation)
class Assistant {
private:
    std::string assistantName;
    CommandParser parser;
    Logger logger;
    bool isRunning;

    // Registers all supported commands into parser
    void initializeCommands();

public:
    explicit Assistant(std::string name = "Hydron");

    // Displays time-of-day greeting
    void greetUser() const;

    // Displays list of supported commands and usage help
    void showHelp() const;

    // Starts the main interactive loop
    void run();
};

#endif // ASSISTANT_H
