#include "NewTabTask.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

NewTabTask::NewTabTask() : Task("New Tab Task") {}

void NewTabTask::execute() {
    std::cout << "[Hydron] Simulating 'Ctrl+T' keypress to open a new tab..." << std::endl;

#ifdef _WIN32
    // Windows API SendInput to simulate Ctrl+T key sequence
    INPUT inputs[4] = {};

    // 1. Press Ctrl key
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;

    // 2. Press T key
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 'T';

    // 3. Release T key
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'T';
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    // 4. Release Ctrl key
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(4, inputs, sizeof(INPUT));
    if (uSent != 4) {
        std::cout << "[Hydron Error] SendInput failed. Sent " << uSent << " inputs." << std::endl;
    } else {
        std::cout << "[Hydron] Sent 'Ctrl+T' shortcut successfully." << std::endl;
    }
#else
    std::cout << "[Hydron Simulation] (SendInput API is Windows-specific; shortcut simulated on non-Windows OS)." << std::endl;
#endif
}
