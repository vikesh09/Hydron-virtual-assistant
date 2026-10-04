#include "HistoryTask.h"

HistoryTask::HistoryTask(const Logger& logger)
    : Task("History Task"), loggerRef(logger) {}

void HistoryTask::execute() {
    loggerRef.printHistory();
}
