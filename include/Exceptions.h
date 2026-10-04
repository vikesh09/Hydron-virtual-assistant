#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Base exception for Hydron Virtual Assistant
class HydronException : public std::runtime_error {
public:
    explicit HydronException(const std::string& message)
        : std::runtime_error(message) {}
};

// Exception thrown when a user enters an unrecognized or malformed command
class InvalidCommandException : public HydronException {
public:
    explicit InvalidCommandException(const std::string& command)
        : HydronException("Unknown or invalid command: '" + command + "'. Type 'help' or check supported commands.") {}
};

#endif // EXCEPTIONS_H
