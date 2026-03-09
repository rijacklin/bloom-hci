#include "../../include/views/AnalyticsView.h"
#include <iostream>

AnalyticsView::AnalyticsView() : BaseView() {
  currentProject = ProjectType::NONE;
  analyticsInProgress = false;
  analyticsProgress = 0.0f;
  showAnalyticsPreview = false;
  selectedAnalyticsUserIndex = 0;
  selectedAnalyticsMetricIndex = 0;
  selectedAnalyticsPeriodIndex = 0;
}

/*
 * Renders analytics screen
 */
void AnalyticsView::render() {
  ImGuiIO &io = getIO();

  // Left side menu
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y), ImGuiCond_Always);

  if (ImGui::Begin("Projects Menu", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoScrollbar)) {
    renderAnalyticsMenu();
  }

  ImGui::End();

  // Right side content
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 200, io.DisplaySize.y),
                           ImGuiCond_Always);

  if (ImGui::Begin("Analytics Content", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderAnalyticsContent();
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void AnalyticsView::setOnProjectSelect(
    std::function<void(ProjectType)> callback) {
  onProjectSelect = callback;
}

void AnalyticsView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void AnalyticsView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

void AnalyticsView::setCurrentProject(ProjectType project) {
  currentProject = project;
}

/*
 * Helper method to clear analytics form
 */
void AnalyticsView::clearForm() {
  showAnalyticsPreview = false;
  analyticsInProgress = false;
  analyticsProgress = 0.0f;
}

/*
 * Declares contents of left side menu for rendering
 */
void AnalyticsView::renderAnalyticsMenu() {
  ImGui::Text("MENU");
  ImGui::Separator();

  // Projects
  if (ImGui::Button("DEPLOY", ImVec2(180, 40))) {
    if (onProjectSelect)
      onProjectSelect(ProjectType::DEPLOY);
  }

  if (ImGui::Button("FLOW", ImVec2(180, 40))) {
    if (onProjectSelect)
      onProjectSelect(ProjectType::FLOW);
  }

  if (ImGui::Button("BLOOM", ImVec2(180, 40))) {
    if (onProjectSelect)
      onProjectSelect(ProjectType::BLOOM);
  }

  // Bottom buttons
  ImGuiIO &io = getIO();
  ImGui::SetCursorPosY(io.DisplaySize.y - 90);
  ImGui::Separator();

  if (ImGui::Button("<= Back to Projects", ImVec2(180, 30)) && onBackRequest) {
    onBackRequest();
  }

  if (ImGui::Button("Exit", ImVec2(180, 30)) && onExitRequest) {
    onExitRequest();
  }
}

/*
 * Declares contents of right main analytics window for rendering
 */
void AnalyticsView::renderAnalyticsContent() {
  // Basic error checking to toggle between displaying analytics dropdowns and
  // repot generation preview
  if (showAnalyticsPreview) {
    renderAnalyticsPreview();
  } else {
    ImGui::Text("Analytics and Report Generation");
    ImGui::Separator();
    ImGui::Spacing();

    // Dropdown contents
    const char *typeOptions[] = {"Users", "Tasks", "Projects"};
    const char *metricOptions[] = {"Tasks Completed", "Time Spent on Task"};
    const char *periodOptions[] = {"Period", "Quarter", "Year"};

    // Options dropdown
    ImGui::Text("Select Type:");
    ImGui::SetNextItemWidth(200);
    ImGui::Combo("##users", &selectedAnalyticsUserIndex, typeOptions,
                 IM_ARRAYSIZE(typeOptions));
    ImGui::Spacing();

    // Metrics dropdown
    ImGui::Text("Select Metric:");
    ImGui::SetNextItemWidth(200);
    ImGui::Combo("##metrics", &selectedAnalyticsMetricIndex, metricOptions,
                 IM_ARRAYSIZE(metricOptions));
    ImGui::Spacing();

    // Period dropdown
    ImGui::Text("Select Time Period:");
    ImGui::SetNextItemWidth(200);
    ImGui::Combo("##period", &selectedAnalyticsPeriodIndex, periodOptions,
                 IM_ARRAYSIZE(periodOptions));
    ImGui::Spacing();
    ImGui::Spacing();

    // Button to perform (mock) analytics
    if (ImGui::Button("Perform Analytics in FLOW", ImVec2(200, 30))) {
      if (!analyticsInProgress) {
        // Start analytics
        analyticsInProgress = true;
        analyticsProgress = 0.0f;
        analyticsStartTime = std::chrono::steady_clock::now();
      }
    }

    // Button to update (mock) analytics progress
    if (analyticsInProgress) {
      // Calculations to simulate analytics processing
      auto currentTime = std::chrono::steady_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
          currentTime - analyticsStartTime);
      float elapsedSeconds = elapsed.count() / 1000.0f;
      analyticsProgress =
          std::min(elapsedSeconds / 3.0f, 1.0f); // 3 seconds total

      // Progress bar
      ImGui::Spacing();
      ImGui::Text("Performing Analytics...");
      ImGui::ProgressBar(analyticsProgress, ImVec2(240, 0), nullptr);

      // track and show analytics progress
      if (analyticsProgress >= 1.0f) {
        analyticsInProgress = false;
        analyticsProgress = 0.0f;
        showAnalyticsPreview = true;
        std::cout << "Analytics completed!" << std::endl;
      }
    }
  }
}

/*
 * Declares contents of (mock) analytics report preview
 */
void AnalyticsView::renderAnalyticsPreview() {
  ImGui::Text("Analytics Report Preview");
  ImGui::Separator();
  ImGui::Spacing();

  // Back button
  if (ImGui::Button("<= Back to Analytics", ImVec2(150, 30))) {
    showAnalyticsPreview = false;
  }

  ImGui::Spacing();
  ImGui::Spacing();

  // Preview
  ImGui::Text("Preview");
  ImGui::BeginChild("PreviewBox", ImVec2(600, 400), true);
  ImGui::Text("Report preview will appear here...");
  ImGui::EndChild();
  ImGui::Spacing();

  // Download and Print buttons (stub functionality)
  if (ImGui::Button("Download", ImVec2(120, 30))) {
    // Stub functionatliy for now...
  }

  ImGui::SameLine();

  if (ImGui::Button("Print", ImVec2(120, 30))) {
    // Stub functionatliy for now...
  }
}

/*
 * Helper method to convert enum type to string representation
 */
std::string AnalyticsView::projectTypeToString(ProjectType project) const {
  switch (project) {
  case ProjectType::DEPLOY:
    return "Deploy";
  case ProjectType::FLOW:
    return "Flow";
  case ProjectType::BLOOM:
    return "Bloom";
  default:
    return "None";
  }
}
