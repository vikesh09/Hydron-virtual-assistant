#include "CommandParser.h"
#include <algorithm>
#include <cctype>
#include <sstream>

std::string CommandParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

std::string CommandParser::toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

void CommandParser::registerCommand(const std::string& keyword, TaskCreator creator) {
    registry[toLower(keyword)] = creator;
}

bool CommandParser::hasCommand(const std::string& keyword) const {
    return registry.find(toLower(keyword)) != registry.end();
}

std::unique_ptr<Task> CommandParser::parse(const std::string& rawInput) const {
    std::string cleaned = trim(rawInput);
    if (cleaned.empty()) {
        throw InvalidCommandException("empty input");
    }

    std::string lowerInput = toLower(cleaned);

    // Check for multi-word commands first (e.g., "new tab")
    for (const auto& [keyword, creator] : registry) {
        if (keyword.find(' ') != std::string::npos) {
            if (lowerInput == keyword) {
                return creator("");
            } else if (lowerInput.rfind(keyword + " ", 0) == 0) {
                std::string arg = cleaned.substr(keyword.length() + 1);
                return creator(trim(arg));
            }
        }
    }

    // Split single-word command and argument
    std::istringstream stream(cleaned);
    std::string commandKeyword;
    stream >> commandKeyword;

    std::string argument;
    std::getline(stream, argument);
    argument = trim(argument);

    std::string lowerKeyword = toLower(commandKeyword);
    auto it = registry.find(lowerKeyword);

    if (it != registry.end()) {
        return it->second(argument);
    }

    // Unrecognized command -> throw exception
    throw InvalidCommandException(cleaned);
}
