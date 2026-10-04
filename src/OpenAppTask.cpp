#include "OpenAppTask.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

OpenAppTask::OpenAppTask(std::string app)
    : Task("Open Application Task"), appName(std::move(app)) {}

void OpenAppTask::execute() {
    if (appName.empty()) {
        std::cout << "[Hydron Error] Application name cannot be empty." << std::endl;
        return;
    }

    std::cout << "[Hydron] Launching application: " << appName << "..." << std::endl;

#ifdef _WIN32
    // Windows system launch command (e.g. start notepad, start calc)
    std::string command = "start " + appName;
    int status = std::system(command.c_str());
    if (status != 0) {
        std::cout << "[Hydron Error] Failed to launch '" << appName << "' via system command." << std::endl;
    }
#elif __APPLE__
    std::string macApp = appName;
    std::string lowerApp = appName;
    std::transform(lowerApp.begin(), lowerApp.end(), lowerApp.begin(), ::tolower);

    // Smart aliases for Mac equivalent apps
    if (lowerApp == "notepad") macApp = "TextEdit";
    else if (lowerApp == "calc" || lowerApp == "calculator") macApp = "Calculator";
    else if (lowerApp == "chrome") macApp = "Google Chrome";

    std::string command = "open -a \"" + macApp + "\"";
    int status = std::system(command.c_str());
    if (status != 0) {
        std::cout << "[Hydron Error] Could not find or open application '" << appName << "'." << std::endl;
    }
#else
    std::string command = "xdg-open " + appName;
    std::system(command.c_str());
#endif
}
