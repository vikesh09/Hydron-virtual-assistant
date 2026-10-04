#include "Task.h"

Task::Task(std::string name) : taskName(std::move(name)) {}

std::string Task::getName() const {
    return taskName;
}
