#ifndef TASK_H
#define TASK_H

#include <string>

// Abstract Base Class representing a generic task (Abstraction)
class Task {
protected:
    std::string taskName;

public:
    explicit Task(std::string name);
    virtual ~Task() = default;

    // Pure virtual method defining task execution (Abstraction & Polymorphism)
    virtual void execute() = 0;

    // Encapsulation: Getter for task name
    std::string getName() const;
};

#endif // TASK_H
