#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "Task.h"
#include "Exceptions.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

// Parser class responsible for mapping command strings to Task instances (Factory & Encapsulation)
class CommandParser {
public:
    using TaskCreator = std::function<std::unique_ptr<Task>(const std::string& argument)>;

private:
    std::unordered_map<std::string, TaskCreator> registry;

    // Helper functions for string manipulation
    static std::string trim(const std::string& str);
    static std::string toLower(const std::string& str);

public:
    CommandParser() = default;

    // Extensible Registration API: Register a keyword with its factory function
    void registerCommand(const std::string& keyword, TaskCreator creator);

    // Parses raw input into a polymorphic Task instance; throws InvalidCommandException if invalid
    std::unique_ptr<Task> parse(const std::string& rawInput) const;

    // Checks if a command is registered
    bool hasCommand(const std::string& keyword) const;
};

#endif // COMMAND_PARSER_H
