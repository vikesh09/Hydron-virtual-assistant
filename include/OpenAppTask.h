#ifndef OPEN_APP_TASK_H
#define OPEN_APP_TASK_H

#include "Task.h"
#include <string>

// Derived Task to open desktop applications (Inheritance)
class OpenAppTask : public Task {
private:
    std::string appName;

public:
    explicit OpenAppTask(std::string app);

    // Polymorphic implementation of execute()
    void execute() override;
};

#endif // OPEN_APP_TASK_H
