#include "../../include/views/AddTaskView.h"

AddTaskView::AddTaskView() : BaseView() {
  currentProject = ProjectType::NONE;
  memset(newTaskTitle, 0, sizeof(newTaskTitle));
  memset(newTaskDescription, 0, sizeof(newTaskDescription));
  selectedTaskUserIndex = 0;
  showTitleError = false;
  errorMessage = "";
}

/*
 * Renders adding task screen
 */
void AddTaskView::render() {
  ImGuiIO &io = getIO();

  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);

  if (ImGui::Begin("Add Task", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse)) {
    // clear the form and direct user back to project tasks screen
    if (ImGui::Button("<= Back", ImVec2(100, 30)) && onBackRequest) {
      clearForm();
      onBackRequest();
    }

    ImGui::Separator();
    ImGui::Spacing();

    // task title
    ImGui::Text("Task Title:");
    if (showTitleError) {
      ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.2f, 0.2f, 0.3f));
      ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,
                            ImVec4(0.8f, 0.2f, 0.2f, 0.4f));
      ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                            ImVec4(0.8f, 0.2f, 0.2f, 0.5f));
    }

    ImGui::InputText("##title", newTaskTitle, sizeof(newTaskTitle),
                     ImGuiInputTextFlags_AllowTabInput);
    if (showTitleError) {
      ImGui::PopStyleColor(3);
    }

    ImGui::Spacing();

    // task assigned to dropdown
    ImGui::Text("Assign To:");
    ImGui::Combo("##assigned", &selectedTaskUserIndex, users,
                 IM_ARRAYSIZE(users));
    ImGui::Spacing();

    // Task descritpoin
    ImGui::Text("Task Description:");
    ImGui::InputTextMultiline("##description", newTaskDescription,
                              sizeof(newTaskDescription), ImVec2(400, 100),
                              ImGuiInputTextFlags_AllowTabInput);
    ImGui::Spacing();

    // Display error message
    if (showTitleError && !errorMessage.empty()) {
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
      ImGui::Text("%s", errorMessage.c_str());
      ImGui::PopStyleColor();
      ImGui::Spacing();
    }

    // Create task
    if (ImGui::Button("Create", ImVec2(100, 30))) {
      // Basic input validation
      if (strlen(newTaskTitle) == 0) {
        showTitleError = true;
        errorMessage = "Task title cannot be empty";
      } else {
        showTitleError = false;
        errorMessage = "";
        if (onTaskCreate) {
          // create the task
          onTaskCreate(std::string(newTaskTitle),
                       std::string(users[selectedTaskUserIndex]),
                       std::string(newTaskDescription), currentProject);
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
void AddTaskView::setOnTaskCreate(
    std::function<void(const std::string &, const std::string &,
                       const std::string &, ProjectType)>
        callback) {
  onTaskCreate = callback;
}

void AddTaskView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void AddTaskView::setCurrentProject(ProjectType project) {
  currentProject = project;
}

/*
 * Helper method to clear form
 */
void AddTaskView::clearForm() {
  memset(newTaskTitle, 0, sizeof(newTaskTitle));
  memset(newTaskDescription, 0, sizeof(newTaskDescription));
  selectedTaskUserIndex = 0;
  showTitleError = false;
  errorMessage = "";
}

/*
 * Helper method to convert enum type to string representation
 */
std::string AddTaskView::projectTypeToString(ProjectType project) const {
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
