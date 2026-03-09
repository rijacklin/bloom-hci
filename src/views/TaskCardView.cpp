#include "../../include/views/TaskCardView.h"

TaskCardView::TaskCardView() : BaseView() {
  currentTaskCard = nullptr;
  currentTaskCardIndex = -1;
  currentProject = ProjectType::NONE;
}

/*
 * Renders single taskcard screen
 */
void TaskCardView::render() {
  ImGuiIO &io = getIO();

  // Left side menu
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y), ImGuiCond_Always);

  if (ImGui::Begin("Task Card View Menu", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoScrollbar)) {
    renderTaskCardMenu();
  }

  ImGui::End();

  // Right side content
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 200, io.DisplaySize.y),
                           ImGuiCond_Always);

  if (ImGui::Begin("Task Card Details", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderTaskCardContent();
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void TaskCardView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void TaskCardView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

void TaskCardView::setOnCalculateTotalStoryPoints(
    std::function<int(ProjectType)> callback) {
  onCalculateTotalStoryPoints = callback;
}

/*
 * Helper method to set current taskcard
 */
void TaskCardView::setCurrentTaskCard(std::unique_ptr<TaskCard> taskCard,
                                      int index, ProjectType project) {
  currentTaskCard = std::move(taskCard);
  currentTaskCardIndex = index;
  currentProject = project;
}

/*
 * Declares contents of left side menu for rendering
 */
void TaskCardView::renderTaskCardMenu() {
  ImGui::Text("MENU");
  ImGui::Separator();

  // Bottom buttons
  ImGuiIO &io = getIO();
  ImGui::SetCursorPosY(io.DisplaySize.y - 90);
  ImGui::Separator();

  if (ImGui::Button("<= Back to Sprint", ImVec2(180, 30)) && onBackRequest) {
    currentTaskCard = nullptr;
    currentTaskCardIndex = -1;
    onBackRequest();
  }

  if (ImGui::Button("Exit", ImVec2(180, 30)) && onExitRequest) {
    onExitRequest();
  }
}

/*
 * Declares contents of right main content window for rendering
 */
void TaskCardView::renderTaskCardContent() {
  // Basic error checking before displaying task
  if (currentTaskCard != nullptr) {
    // title
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Text("Sprint Task: %s", currentTaskCard->getTitle().c_str());
    ImGui::PopFont();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Assigned to
    ImGui::Text("Assigned To:");
    ImGui::SameLine(150);
    ImGui::Text("%s", currentTaskCard->getAssignedTo().c_str());

    ImGui::Spacing();

    // Project
    ImGui::Text("Project:");
    ImGui::SameLine(150);
    std::string projectName = projectTypeToString(currentProject);
    ImGui::Text("%s", projectName.c_str());

    ImGui::Spacing();

    // Story points
    ImGui::Text("Story Points:");
    ImGui::SameLine(150);
    ImGui::Text("%d", currentTaskCard->getStoryPoints());

    ImGui::Spacing();
    ImGui::Spacing();

    // Sprint summary
    ImGui::Text("Sprint Task Summary:");
    ImGui::Separator();
    ImGui::Spacing();

    // Calculate and display total sprint story points (dynamic UI)
    int totalSprintPoints = 0;

    if (onCalculateTotalStoryPoints) {
      totalSprintPoints = onCalculateTotalStoryPoints(currentProject);
    }

    ImGui::Text("Total Sprint Story Points: %d", totalSprintPoints);

    // Calculate and display task card contribution percentage
    if (totalSprintPoints > 0) {
      float percentage = (float(currentTaskCard->getStoryPoints()) /
                          float(totalSprintPoints)) *
                         100.0f;
      ImGui::Text("%.1f%% contribution to total sprint", percentage);
    }

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Action buttons
    if (ImGui::Button("Edit Task Card", ImVec2(120, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete Task Card", ImVec2(120, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::Spacing();

    // Additional sprint management buttons
    if (ImGui::Button("Move to Next Sprint", ImVec2(140, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::SameLine();

    if (ImGui::Button("Change Story Points", ImVec2(140, 30))) {
      // Stub functionatliy for now...
    }
  } else {
    // Display basic error state
    ImGui::Text("Error: No task card selected");
  }
}

/*
 * Helper method to convert enum type to string representation
 */
std::string TaskCardView::projectTypeToString(ProjectType project) const {
  switch (project) {
  case ProjectType::DEPLOY:
    return "DEPLOY";
  case ProjectType::FLOW:
    return "FLOW";
  case ProjectType::BLOOM:
    return "BLOOM";
  default:
    return "NONE";
  }
}
