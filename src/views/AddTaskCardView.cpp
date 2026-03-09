#include "../../include/views/AddTaskCardView.h"

AddTaskCardView::AddTaskCardView() : BaseView() {
  currentProject = ProjectType::NONE;
  memset(newTaskCardTitle, 0, sizeof(newTaskCardTitle));

  // start taskcard with default storypoints value of 1 to assist user
  newTaskCardStoryPts = 1;
  selectedSprintTaskUserIndex = 0;
  showTitleError = false;
  errorMessage = "";
}

/*
 * Renders adding task screen
 */
void AddTaskCardView::render() {
  ImGuiIO &io = getIO();

  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);

  if (ImGui::Begin("Add Task Card", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse)) {
    // clear the form and direct user back to project sprint screen
    if (ImGui::Button("<= Back", ImVec2(100, 30)) && onBackRequest) {
      clearForm();
      onBackRequest();
    }

    ImGui::Separator();
    ImGui::Spacing();

    // Taskcard title
    ImGui::Text("Task Card Title:");
    if (showTitleError) {
      ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.2f, 0.2f, 0.3f));
      ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,
                            ImVec4(0.8f, 0.2f, 0.2f, 0.4f));
      ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                            ImVec4(0.8f, 0.2f, 0.2f, 0.5f));
    }

    ImGui::InputText("##title", newTaskCardTitle, sizeof(newTaskCardTitle),
                     ImGuiInputTextFlags_AllowTabInput);
    if (showTitleError) {
      ImGui::PopStyleColor(3);
    }

    // task card assigned to
    ImGui::Spacing();
    ImGui::Text("Assign To:");
    ImGui::Combo("##assigned", &selectedSprintTaskUserIndex, users,
                 IM_ARRAYSIZE(users));
    ImGui::Spacing();

    // task card story points
    ImGui::Text("Story Points:");
    ImGui::InputInt("##storypts", &newTaskCardStoryPts);
    ImGui::Spacing();

    // Display error message
    if (showTitleError && !errorMessage.empty()) {
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
      ImGui::Text("%s", errorMessage.c_str());
      ImGui::PopStyleColor();
      ImGui::Spacing();
    }

    // Create task card
    if (ImGui::Button("Create", ImVec2(100, 30))) {
      // Basic input validation
      if (strlen(newTaskCardTitle) == 0) {
        showTitleError = true;
        errorMessage = "Taskcard title cannot be empty";
      } else if (newTaskCardStoryPts <= 0) {
        // Ensure story points aren't at 0
        showTitleError = true;
        errorMessage = "Story points must be greater than 0";
      } else {
        showTitleError = false;
        errorMessage = "";
        if (onTaskCardCreate) {
          // create thte task card
          onTaskCardCreate(std::string(newTaskCardTitle),
                           std::string(users[selectedSprintTaskUserIndex]),
                           newTaskCardStoryPts, currentProject);
          clearForm();
        }
      }
    }
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void AddTaskCardView::setOnTaskCardCreate(
    std::function<void(const std::string &, const std::string &, int,
                       ProjectType)>
        callback) {
  onTaskCardCreate = callback;
}

void AddTaskCardView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void AddTaskCardView::setCurrentProject(ProjectType project) {
  currentProject = project;
}

/*
 * Helper method to clear form
 */
void AddTaskCardView::clearForm() {
  memset(newTaskCardTitle, 0, sizeof(newTaskCardTitle));
  newTaskCardStoryPts = 0;
  selectedSprintTaskUserIndex = 0;
  showTitleError = false;
  errorMessage = "";
}

/*
 * Helper method to convert enum type to string representation
 */
std::string AddTaskCardView::projectTypeToString(ProjectType project) const {
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
