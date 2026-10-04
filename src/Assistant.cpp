#include "Assistant.h"
#include "TimeTask.h"
#include "OpenAppTask.h"
#include "SearchTask.h"
#include "NewTabTask.h"
#include "HistoryTask.h"
#include "Exceptions.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>

Assistant::Assistant(std::string name)
    : assistantName(std::move(name)), logger("history.txt"), isRunning(false) {
    initializeCommands();
}

void Assistant::initializeCommands() {
    // 1. Time / Date Command Registration
    parser.registerCommand("time", [](const std::string&) {
        return std::make_unique<TimeTask>();
    });
    parser.registerCommand("date", [](const std::string&) {
        return std::make_unique<TimeTask>();
    });

    // 2. Open Application Command Registration
    parser.registerCommand("open", [](const std::string& arg) {
        return std::make_unique<OpenAppTask>(arg);
    });

    // 3. Web Search Command Registration
    parser.registerCommand("search", [](const std::string& arg) {
        return std::make_unique<SearchTask>(arg);
    });

    // 4. New Tab Shortcut Command Registration
    parser.registerCommand("new tab", [](const std::string&) {
        return std::make_unique<NewTabTask>();
    });

    // 5. Command History Registration
    parser.registerCommand("history", [this](const std::string&) {
        return std::make_unique<HistoryTask>(this->logger);
    });
}

void Assistant::greetUser() const {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* timeInfo = std::localtime(&currentTime);
    int hour = timeInfo->tm_hour;

    std::string greeting;
    if (hour >= 5 && hour < 12) {
        greeting = "Good morning!";
    } else if (hour >= 12 && hour < 17) {
        greeting = "Good afternoon!";
    } else {
        greeting = "Good evening!";
    }

    std::cout << "=========================================================\n";
    std::cout << " " << greeting << " I am " << assistantName << ", your Virtual Assistant.\n";
    std::cout << " Type 'help' to view supported commands or 'exit' to quit.\n";
    std::cout << "=========================================================\n";
}

void Assistant::showHelp() const {
    std::cout << "\n---------------- Supported Commands ----------------\n";
    std::cout << " 1. time / date      : Print current date and time\n";
    std::cout << " 2. open <app>       : Open app (e.g., open notepad, open calc)\n";
    std::cout << " 3. search <query>   : Search query on Google in browser\n";
    std::cout << " 4. new tab          : Simulate Ctrl+T shortcut for new tab\n";
    std::cout << " 5. history          : Show command history log\n";
    std::cout << " 6. help             : Show this help menu\n";
    std::cout << " 7. exit             : Exit Hydron\n";
    std::cout << "----------------------------------------------------\n";
}

void Assistant::run() {
    isRunning = true;
    greetUser();

    std::string userInput;
    while (isRunning) {
        std::cout << "\n" << assistantName << " > ";
        if (!std::getline(std::cin, userInput)) {
            break; // Handle EOF / Ctrl+C
        }

        // Trim input
        size_t first = userInput.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) continue;
        size_t last = userInput.find_last_not_of(" \t\r\n");
        std::string trimmedInput = userInput.substr(first, (last - first + 1));

        if (trimmedInput.empty()) continue;

        // Log input to history file
        logger.logCommand(trimmedInput);

        // Lowercase check for built-in loop controls
        std::string lowerInput = trimmedInput;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

        if (lowerInput == "exit" || lowerInput == "quit") {
            std::cout << "[" << assistantName << "] Goodbye! Have a great day." << std::endl;
            isRunning = false;
            break;
        }

        if (lowerInput == "help") {
            showHelp();
            continue;
        }

        // Execute task via polymorphic task interface with robust exception handling
        try {
            std::unique_ptr<Task> task = parser.parse(trimmedInput);
            task->execute(); // Polymorphic method call
        } catch (const InvalidCommandException& ex) {
            std::cout << "[Hydron] " << ex.what() << std::endl;
        } catch (const std::exception& ex) {
            std::cout << "[Hydron Error] Unexpected runtime error: " << ex.what() << std::endl;
        }
    }
}
