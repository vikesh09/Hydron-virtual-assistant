#ifndef NEW_TAB_TASK_H
#define NEW_TAB_TASK_H

#include "Task.h"

// Derived Task to simulate opening a new browser tab via Ctrl+T (Inheritance & Win32 API)
class NewTabTask : public Task {
public:
    NewTabTask();

    // Polymorphic implementation of execute()
    void execute() override;
};

#endif // NEW_TAB_TASK_H
