#ifndef ANALYTICSVIEW_H
#define ANALYTICSVIEW_H

#include "BaseView.h"
#include "models/Task.h"
#include <chrono>
#include <functional>

class AnalyticsView : public BaseView {
private:
  ProjectType currentProject;

  // Analytics state
  bool analyticsInProgress;
  float analyticsProgress;
  std::chrono::steady_clock::time_point analyticsStartTime;
  bool showAnalyticsPreview;

  // Selection indices
  int selectedAnalyticsUserIndex;
  int selectedAnalyticsMetricIndex;
  int selectedAnalyticsPeriodIndex;

  // Callback functions for user actions
  std::function<void(ProjectType)> onProjectSelect;
  std::function<void()> onBackRequest;
  std::function<void()> onExitRequest;

public:
  AnalyticsView();
  ~AnalyticsView() = default;

  // Override from BaseView
  void render() override;

  // Setters for callbacks
  void setOnProjectSelect(std::function<void(ProjectType)> callback);
  void setOnBackRequest(std::function<void()> callback);
  void setOnExitRequest(std::function<void()> callback);

  // Set data
  void setCurrentProject(ProjectType project);

  // Reset analytics state to show dropdowns
  void clearForm();

private:
  void renderAnalyticsMenu();
  void renderAnalyticsContent();
  void renderAnalyticsPreview();
  std::string projectTypeToString(ProjectType project) const;
};

#endif // AnalyticsView.h
