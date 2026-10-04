#include "SearchTask.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

SearchTask::SearchTask(std::string searchQuery)
    : Task("Web Search Task"), query(std::move(searchQuery)) {}

std::string SearchTask::urlEncodeQuery(const std::string& input) {
    std::string encoded;
    for (char c : input) {
        if (c == ' ') {
            encoded += "+";
        } else {
            encoded += c;
        }
    }
    return encoded;
}

void SearchTask::execute() {
    if (query.empty()) {
        std::cout << "[Hydron Error] Search query cannot be empty." << std::endl;
        return;
    }

    std::string encodedQuery = urlEncodeQuery(query);
    std::string searchUrl = "https://www.google.com/search?q=" + encodedQuery;

    std::cout << "[Hydron] Searching Google for: \"" << query << "\"..." << std::endl;

#ifdef _WIN32
    std::string command = "start " + searchUrl;
    std::system(command.c_str());
#elif __APPLE__
    std::string command = "open \"" + searchUrl + "\"";
    std::system(command.c_str());
#else
    std::string command = "xdg-open \"" + searchUrl + "\"";
    std::system(command.c_str());
#endif
}
