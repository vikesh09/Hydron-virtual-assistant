#ifndef TIME_TASK_H
#define TIME_TASK_H

#include "Task.h"

// Derived Task to handle time and date queries (Inheritance)
class TimeTask : public Task {
public:
    TimeTask();
    
    // Polymorphic implementation of execute()
    void execute() override;
};

#endif // TIME_TASK_H
