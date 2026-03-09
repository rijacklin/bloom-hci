#ifndef ANALYTICSCONTROLLER_H
#define ANALYTICSCONTROLLER_H

#include "../models/Task.h"
#include "../models/TaskCard.h"
#include <chrono>
#include <string>
#include <vector>

// Required forward declarations
class TaskController;
class TaskCardController;

struct AnalyticsRequest {
  std::string user;
  std::string metric;
  std::string period;
};

struct AnalyticsResult {
  bool isComplete;
  float progress;
  std::string previewData;
  std::string reportData;
};

class AnalyticsController {
private:
  TaskController *taskController;
  TaskCardController *taskCardController;
  AnalyticsResult currentAnalytics;
  std::chrono::steady_clock::time_point analyticsStart;
  bool analyticsInProgress;

public:
  AnalyticsController(TaskController *taskController,
                      TaskCardController *tcController);
  ~AnalyticsController() = default;
};

#endif // AnalyticsController.h
