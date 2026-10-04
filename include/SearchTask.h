#ifndef SEARCH_TASK_H
#define SEARCH_TASK_H

#include "Task.h"
#include <string>

// Derived Task to perform Google web searches in default browser (Inheritance)
class SearchTask : public Task {
private:
    std::string query;

    // Helper method to format query string for URL
    static std::string urlEncodeQuery(const std::string& input);

public:
    explicit SearchTask(std::string searchQuery);

    // Polymorphic implementation of execute()
    void execute() override;
};

#endif // SEARCH_TASK_H
