# 📘 HYDRON VIRTUAL ASSISTANT: 6 CORE FUNCTIONS WORKING & TECHNICAL GUIDE

This document provides a detailed breakdown of how each of the **6 core functions** in Hydron works under the hood, including the C++ classes involved, OOP concepts demonstrated, internal working logic, and APIs used.

---

## 📄 1. `time` / `date` (System Clock Query)

* **User Command:** `time`  OR  `date`
* **Class & File:** `TimeTask` ([`TimeTask.h`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/include/TimeTask.h), [`TimeTask.cpp`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/src/TimeTask.cpp))
* **OOP Concept:** **Inheritance & Dynamic Polymorphism**
* **How It Works (Internal Logic):**
  1. User types `time` or `date`.
  2. `CommandParser` matches the keyword and returns `std::make_unique<TimeTask>()`.
  3. `TimeTask::execute()` uses the standard C++ `<chrono>` library (`std::chrono::system_clock::now()`) and `<ctime>` (`std::localtime()`) to fetch system clock data.
  4. It extracts year, month, date, hour, minute, second, and day of week.
  5. Formats and prints output: `[Hydron] Current Date and Time: 2026-10-04 19:30:00 (Sunday)`.

---

## 📄 2. `open <app>` (Desktop Application Launcher)

* **User Command:** `open notepad`  /  `open calc`  /  `open safari`  /  `open chrome`
* **Class & File:** `OpenAppTask` ([`OpenAppTask.h`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/include/OpenAppTask.h), [`OpenAppTask.cpp`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/src/OpenAppTask.cpp))
* **OOP Concept:** **Inheritance, Polymorphism, Platform Abstraction**
* **How It Works (Internal Logic):**
  1. `CommandParser` splits `open` (keyword) and `<app>` (argument, e.g., `notepad`).
  2. Creates `std::make_unique<OpenAppTask>(appName)`.
  3. **Windows OS:** Executes `std::system("start <app>")` which invokes Windows command shell to open native apps like `notepad.exe` or `calc.exe`.
  4. **macOS:** Maps app aliases (`notepad` $\rightarrow$ `TextEdit`, `calc` $\rightarrow$ `Calculator`) and executes `open -a "<app>"`.

---

## 📄 3. `search <query>` (Web Search Automation)

* **User Command:** `search C++ OOP concepts`
* **Class & File:** `SearchTask` ([`SearchTask.h`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/include/SearchTask.h), [`SearchTask.cpp`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/src/SearchTask.cpp))
* **OOP Concept:** **Inheritance, Polymorphism, Helper Encapsulation**
* **How It Works (Internal Logic):**
  1. `CommandParser` extracts the search string (e.g. `C++ OOP concepts`).
  2. Creates `std::make_unique<SearchTask>(query)`.
  3. `SearchTask::urlEncodeQuery()` replaces spaces with `+` (`C+++OOP+concepts`).
  4. Appends query to Google search URL: `https://www.google.com/search?q=C+++OOP+concepts`.
  5. Launches the default browser using OS system call (`start <url>` on Windows / `open <url>` on Mac).

---

## 📄 4. `new tab` (Keyboard Input Automation)

* **User Command:** `new tab`
* **Class & File:** `NewTabTask` ([`NewTabTask.h`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/include/NewTabTask.h), [`NewTabTask.cpp`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/src/NewTabTask.cpp))
* **OOP Concept:** **Inheritance & Win32 API Integration**
* **How It Works (Internal Logic):**
  1. User types `new tab`.
  2. `CommandParser` matches multi-word keyword and creates `std::make_unique<NewTabTask>()`.
  3. `NewTabTask::execute()` uses the **Windows Win32 `SendInput()` API**.
  4. Constructs an array of 4 `INPUT` key event structures:
     - `VK_CONTROL` Key Down
     - `'T'` Key Down
     - `'T'` Key Up
     - `VK_CONTROL` Key Up
  5. Injects key sequence into OS message queue to simulate `Ctrl + T` browser shortcut.

---

## 📄 5. `history` (Command Log Persistence)

* **User Command:** `history`
* **Class & File:** `HistoryTask` ([`HistoryTask.h`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/include/HistoryTask.h), [`HistoryTask.cpp`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/src/HistoryTask.cpp)) & `Logger` ([`Logger.h`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/include/Logger.h), [`Logger.cpp`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/src/Logger.cpp))
* **OOP Concept:** **File Handling (I/O Streams) & Encapsulation**
* **How It Works (Internal Logic):**
  1. Every command typed by user is automatically logged by `Logger::logCommand()` into `history.txt` using `std::ofstream` in `std::ios::app` mode with `[YYYY-MM-DD HH:MM:SS]` timestamp.
  2. When user types `history`, `HistoryTask::execute()` calls `Logger::printHistory()`.
  3. `Logger::printHistory()` opens `history.txt` via `std::ifstream` and prints all logged lines numbered to console.

---

## 📄 6. `exit` / `quit` & `help` (Lifecycle & Assistance)

* **User Command:** `exit`  /  `quit`  /  `help`
* **Class & File:** `Assistant` ([`Assistant.h`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/include/Assistant.h), [`Assistant.cpp`](file:///Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/src/Assistant.cpp))
* **OOP Concept:** **Encapsulation & REPL Control Loop**
* **How It Works (Internal Logic):**
  1. `Assistant::run()` manages the interactive REPL while-loop (`while(isRunning)`).
  2. On typing `help`, `showHelp()` displays the supported command menu.
  3. On typing `exit` or `quit`, `Assistant` prints farewell message (`"Goodbye! Have a great day."`), sets `isRunning = false`, and breaks loop cleanly.

---

## 🔄 Execution Pipeline Architecture Flow

```text
[User Input] 
     │
     ▼
[Assistant::run()] ──> [Logger::logCommand()] (Appends to history.txt)
     │
     ▼
[CommandParser::parse()] (Parses input & returns std::unique_ptr<Task>)
     │
     ▼
[task->execute()] (Dynamic Polymorphic Execution)
     │
     ▼
[Console Output / System Action]
```
