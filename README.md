# Hydron Virtual Assistant (C++ OOP Project)

**Hydron** is a lightweight, Windows console-based virtual assistant written in modern C++17. Designed as an Object-Oriented Programming (OOP) demonstration project, it showcases core OOP principles including Abstraction, Polymorphism, Inheritance, Encapsulation, Exception Handling, File I/O, and the Command Factory Pattern.

---

## 🚀 Features & Commands

Hydron supports the following MVP commands:

| Command | Description | Example |
| :--- | :--- | :--- |
| `time` / `date` | Displays the current date, time, and day of the week | `time` |
| `open <app>` | Opens external desktop applications | `open notepad` / `open calc` |
| `search <query>` | Performs a web search in the default web browser | `search C++ OOP tutorial` |
| `new tab` | Simulates `Ctrl + T` keypress via Windows `SendInput()` API | `new tab` |
| `history` | Prints the logged command history from `history.txt` | `history` |
| `help` | Displays the help menu with supported commands | `help` |
| `exit` / `quit` | Terminates the assistant session cleanly | `exit` |

*Note: Hydron greets the user automatically with "Good morning", "Good afternoon", or "Good evening" depending on the system time upon startup.*

---

## 🛠️ Folder Structure

```
project_hydron-virtual/
├── main.cpp                 # Entry point
├── include/                 # Header files
│   ├── Task.h               # Abstract base class for tasks (Abstraction)
│   ├── TimeTask.h           # Derived task for time/date (Inheritance)
│   ├── OpenAppTask.h        # Derived task for launching apps (Inheritance)
│   ├── SearchTask.h         # Derived task for browser web search (Inheritance)
│   ├── NewTabTask.h         # Derived task for Windows SendInput API (Inheritance)
│   ├── HistoryTask.h        # Derived task for reading history (Inheritance)
│   ├── CommandParser.h      # Command registration & task factory (Encapsulation)
│   ├── Logger.h             # History file logging & reading (File Handling)
│   ├── Assistant.h          # Controller class managing REPL loop (Encapsulation)
│   └── Exceptions.h         # Custom exception classes (Exception Handling)
├── src/                     # C++ implementation files
│   ├── Task.cpp
│   ├── TimeTask.cpp
│   ├── OpenAppTask.cpp
│   ├── SearchTask.cpp
│   ├── NewTabTask.cpp
│   ├── HistoryTask.cpp
│   ├── CommandParser.cpp
│   ├── Logger.cpp
│   └── Assistant.cpp
├── history.txt              # Auto-generated command log file
└── README.md                # Project documentation & viva guide
```

---

## 💻 How to Build & Run

### Prerequisites
- Windows OS (or cross-compilation environment)
- MinGW C++ compiler (`g++`) with C++17 support

### Command Line Build

Navigate to the project root directory and run:

```bash
g++ -std=c++17 main.cpp src/*.cpp -Iinclude -o hydron.exe
```

### Running the Application

```cmd
hydron.exe
```

---

## 🎓 Viva Guide: OOP Concepts Explanation

Below is a breakdown of how each class in **Hydron** maps to fundamental Object-Oriented Programming concepts:

### 1. **Abstraction (`Task.h`)**
* **Class:** `Task`
* **Concept:** Abstraction hides complex implementation details and exposes only essential interfaces. `Task` is an **abstract base class** containing a pure virtual function: `virtual void execute() = 0;`.
* **Viva Note:** Any concrete task must implement `execute()`, providing a uniform contract without exposing internal logic.

### 2. **Inheritance & Polymorphism (`TimeTask`, `OpenAppTask`, `SearchTask`, `NewTabTask`, `HistoryTask`)**
* **Classes:** `TimeTask`, `OpenAppTask`, `SearchTask`, `NewTabTask`, `HistoryTask` derived from `Task`.
* **Concept:**
  * **Inheritance:** Derived classes inherit base properties (`taskName`) and method signatures from `Task`.
  * **Polymorphism:** The `Assistant` class executes commands polymorphically via `std::unique_ptr<Task>`. Calling `task->execute()` dynamically invokes the appropriate overridden method at runtime without needing to know the exact concrete type.

### 3. **Encapsulation (`CommandParser`, `Logger`, `Assistant`)**
* **Classes:** `CommandParser`, `Logger`, `Assistant`
* **Concept:** Hiding data members (marked `private`/`protected`) and controlling access through public member functions.
* **Viva Note:** `Logger` hides the `logFilePath` and file handles; `CommandParser` hides its command registry map; `Assistant` encapsulates the state (`isRunning`) and internal execution loop.

### 4. **Exception Handling (`Exceptions.h`)**
* **Classes:** `HydronException`, `InvalidCommandException`
* **Concept:** Custom exception hierarchy derived from `std::runtime_error` / `std::exception`.
* **Viva Note:** Invalid user inputs throw an `InvalidCommandException`, caught in `Assistant::run()` to present a friendly error message without crashing the application.

### 5. **File Handling (`Logger.cpp`)**
* **Class:** `Logger`
* **Concept:** Persistence using standard C++ file streams (`std::ofstream` to append commands with timestamps and `std::ifstream` to read `history.txt`).

### 6. **Extensible Factory / Command Registry Pattern (`CommandParser.cpp`)**
* **Class:** `CommandParser`
* **Design Advantage:** `CommandParser` maintains a hash map of command keywords to lambda builder functions (`std::function<std::unique_ptr<Task>(const std::string&)>`).
* **Adding New Commands:** To add a new command in the future, you only need to create a new `Task` subclass and add one registration line in `Assistant::initializeCommands()`.
