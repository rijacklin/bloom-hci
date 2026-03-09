#include "../../include/controllers/AnalyticsController.h"
#include "../../include/controllers/TaskCardController.h"
#include "../../include/controllers/TaskController.h"

AnalyticsController::AnalyticsController(TaskController *taskController,
                                         TaskCardController *tcController)
    : taskController(taskController), taskCardController(tcController),
      analyticsInProgress(false) {
  currentAnalytics.isComplete = false;
  currentAnalytics.progress = 0.0f;
}
