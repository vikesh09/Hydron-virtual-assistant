#include "Assistant.h"
#include <iostream>

int main() {
    try {
        Assistant hydron("Hydron");
        hydron.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
