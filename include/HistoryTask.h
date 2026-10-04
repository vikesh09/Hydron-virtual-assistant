#ifndef HISTORY_TASK_H
#define HISTORY_TASK_H

#include "Task.h"
#include "Logger.h"

// Derived Task to print history file contents (Inheritance & Polymorphism)
class HistoryTask : public Task {
private:
    const Logger& loggerRef;

public:
    explicit HistoryTask(const Logger& logger);

    // Polymorphic implementation of execute()
    void execute() override;
};

#endif // HISTORY_TASK_H
