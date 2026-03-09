#include "../../include/views/ProjectsView.h"

ProjectsView::ProjectsView() : BaseView() {
  currentProject = ProjectType::NONE;
  viewMode = TaskViewMode::Tasks;
  tasks = nullptr;
  taskCards = nullptr;
  wikiPages = nullptr;
}

/*
 * Renders projects screen
 */
void ProjectsView::render() {
  ImGuiIO &io = getIO();

  // Left side menu
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y), ImGuiCond_Always);

  if (ImGui::Begin("Projects Menu", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoScrollbar)) {
    renderProjectMenu();
  }

  ImGui::End();

  // Right side content
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 200, io.DisplaySize.y),
                           ImGuiCond_Always);

  if (ImGui::Begin("Projects Content", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderProjectContent();
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void ProjectsView::setOnProjectSelect(
    std::function<void(ProjectType)> callback) {
  onProjectSelect = callback;
}

void ProjectsView::setOnAddTaskRequest(std::function<void()> callback) {
  onAddTaskRequest = callback;
}

void ProjectsView::setOnAddTaskCardRequest(std::function<void()> callback) {
  onAddTaskCardRequest = callback;
}

void ProjectsView::setOnTaskSelect(
    std::function<void(int, ProjectType)> callback) {
  onTaskSelect = callback;
}

void ProjectsView::setOnTaskCardSelect(
    std::function<void(int, ProjectType)> callback) {
  onTaskCardSelect = callback;
}

void ProjectsView::setOnAnalyticsRequest(std::function<void()> callback) {
  onAnalyticsRequest = callback;
}

void ProjectsView::setOnWikiRequest(std::function<void()> callback) {
  onWikiRequest = callback;
}

void ProjectsView::setOnAddWikiPageRequest(std::function<void()> callback) {
  onAddWikiPageRequest = callback;
}

void ProjectsView::setOnWikiPageSelect(
    std::function<void(int, ProjectType)> callback) {
  onWikiPageSelect = callback;
}

void ProjectsView::setOnViewModeChange(
    std::function<void(TaskViewMode)> callback) {
  onViewModeChange = callback;
}

void ProjectsView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void ProjectsView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

/*
 * Helper method to set current project
 */
void ProjectsView::setCurrentProject(ProjectType project) {
  currentProject = project;
}

/*
 * Helper method to set current task view mode
 */
void ProjectsView::setViewMode(TaskViewMode mode) { viewMode = mode; }

/*
 * Setter to initialize project's tasks
 */
void ProjectsView::setTasks(const std::vector<std::unique_ptr<Task>> *tasks) {
  this->tasks = tasks;
}

/*
 * Setter to initialize project's taskcards
 */
void ProjectsView::setTaskCards(
    const std::vector<std::unique_ptr<TaskCard>> *taskCards) {
  this->taskCards = taskCards;
}

/*
 * Setter to initialize project's wikii pages
 */
void ProjectsView::setWikiPages(
    const std::vector<std::unique_ptr<WikiPage>> *wikiPages) {
  this->wikiPages = wikiPages;
}

/*
 * Helper method to sum total story points in sprint
 */
int ProjectsView::calculateTotalStoryPoints() const {
  int total = 0;
  if (taskCards) {
    for (const auto &card : *taskCards) {
      if (card && card->getProject() == currentProject) {
        total += card->getStoryPoints();
      }
    }
  }
  return total;
}

/*
 * Declares contents of left side menu for rendering
 */
void ProjectsView::renderProjectMenu() {
  ImGui::Text("MENU");
  ImGui::Separator();

  // Project buttons
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

  if (ImGui::Button("<= Back to Menu", ImVec2(180, 30)) && onBackRequest) {
    onBackRequest();
  }

  if (ImGui::Button("Exit", ImVec2(180, 30)) && onExitRequest) {
    onExitRequest();
  }
}

/*
 * Declares contents of right main content window for rendering
 */
void ProjectsView::renderProjectContent() {
  // Basic error checking before displaying project
  if (currentProject != ProjectType::NONE) {
    // Display project-specific buttons across the top
    renderProjectButtons();

    // Displays content in window below baed on current view mode
    if (viewMode == TaskViewMode::Tasks) {
      renderTaskList();
    } else if (viewMode == TaskViewMode::Sprint) {
      renderSprintList();
    } else if (viewMode == TaskViewMode::Wiki) {
      renderWikiList();
    }
  } else {
    // Display default view
    ImGuiIO &io = getIO();
    ImGui::SetCursorPosY(io.DisplaySize.y * 0.4f);
    std::string welcomeMsg = "PROJECTS";
    float textWidth = ImGui::CalcTextSize(welcomeMsg.c_str()).x;
    ImGui::SetCursorPosX((io.DisplaySize.x - 200 - textWidth) * 0.5f);
    ImGui::Text("%s", welcomeMsg.c_str());

    ImGui::SetCursorPosX((io.DisplaySize.x - 200 - 300) * 0.5f);
    ImGui::Text("Please select a project from the menu on the left.");
  }
}

/*
 * Declares project buttons across the top and handles rendering view mode
 * changes properly
 */
void ProjectsView::renderProjectButtons() {
  switch (currentProject) {
  case ProjectType::DEPLOY:
    ImGui::Text("DEPLOY");
    break;
  case ProjectType::FLOW:
    ImGui::Text("FLOW");
    break;
  case ProjectType::BLOOM:
    ImGui::Text("BLOOM");
    break;
  default:
    ImGui::Text("NO PROJECT SELECTED");
    break;
  }

  ImGui::Separator();
  ImGui::Spacing();

  if (ImGui::Button("Analytics", ImVec2(120, 30)) && onAnalyticsRequest) {
    onAnalyticsRequest();
  }

  ImGui::SameLine();

  if (ImGui::Button("Tasks", ImVec2(120, 30))) {
    setViewMode(TaskViewMode::Tasks);
    if (onViewModeChange)
      onViewModeChange(TaskViewMode::Tasks);
  }

  ImGui::SameLine();

  if (ImGui::Button("Sprint", ImVec2(120, 30))) {
    setViewMode(TaskViewMode::Sprint);
    if (onViewModeChange)
      onViewModeChange(TaskViewMode::Sprint);
  }

  ImGui::SameLine();

  if (ImGui::Button("Wiki", ImVec2(120, 30))) {
    setViewMode(TaskViewMode::Wiki);
    if (onViewModeChange)
      onViewModeChange(TaskViewMode::Wiki);
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();
}

/*
 * Handles task layout
 */
void ProjectsView::renderTaskList() {
  ImGui::Text("Task Management");
  ImGui::Separator();
  ImGui::Spacing();

  if (ImGui::Button("Add Task", ImVec2(120, 30)) && onAddTaskRequest) {
    onAddTaskRequest();
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Text("Tasks:");
  ImGui::Spacing();

  // Display tasks for current project
  if (tasks && !tasks->empty()) {
    // iterates over tasks
    for (size_t i = 0; i < tasks->size(); ++i) {
      const auto &task = (*tasks)[i];
      if (task && task->getProject() == currentProject) {
        ImGui::BeginChild(("Task##" + task->getTitle()).c_str(), ImVec2(0, 80),
                          true);

        // Handle task click to view
        if (ImGui::Selectable(task->getTitle().c_str(), false,
                              ImGuiSelectableFlags_None, ImVec2(0, 25)) &&
            onTaskSelect) {
          onTaskSelect(static_cast<int>(i), currentProject);
        }

        ImGui::Text("%s", task->getAssignedTo().c_str());
        ImGui::Text("%s", task->getDescription().c_str());
        ImGui::EndChild();
        ImGui::Spacing();
      }
    }
  } else {
    // Basic error handling
    ImGui::Text("No tasks found for this project.");
  }
}

/*
 * Handles sprint taskcard layout
 */
void ProjectsView::renderSprintList() {
  ImGui::Text("Sprint Management");
  ImGui::Separator();
  ImGui::Spacing();

  if (ImGui::Button("Add Task Card", ImVec2(120, 30)) && onAddTaskCardRequest) {
    onAddTaskCardRequest();
  }

  ImGui::Spacing();
  ImGui::Separator();

  // Display total story points for current sprint
  int totalStoryPoints = calculateTotalStoryPoints();
  ImGui::Text("Current Sprint | Story Points: %d", totalStoryPoints);

  ImGui::Spacing();

  // Display taskcards for current project
  if (taskCards && !taskCards->empty()) {
    // Iterates over taskcards
    for (size_t i = 0; i < taskCards->size(); ++i) {
      const auto &taskCard = (*taskCards)[i];
      if (taskCard && taskCard->getProject() == currentProject) {
        ImGui::BeginChild(("TaskCard##" + taskCard->getTitle()).c_str(),
                          ImVec2(0, 90), true);

        // Handle taskcard click to view
        if (ImGui::Selectable(taskCard->getTitle().c_str(), false,
                              ImGuiSelectableFlags_None, ImVec2(0, 25)) &&
            onTaskCardSelect) {
          onTaskCardSelect(static_cast<int>(i), currentProject);
        }

        // Display details of taskcard
        ImGui::Text("Assigned: %s", taskCard->getAssignedTo().c_str());
        ImGui::SameLine(200);
        ImGui::Text("Story Points: %d", taskCard->getStoryPoints());

        ImGui::EndChild();
        ImGui::Spacing();
      }
    }
  } else {
    // Basic error handling
    ImGui::Text("No task cards found for this sprint");
  }
}

/*
 * Handles wiki layout
 */
void ProjectsView::renderWikiList() {
  ImGui::Text("Project Documentation");
  ImGui::Separator();
  ImGui::Spacing();

  if (ImGui::Button("Add Wiki Page", ImVec2(120, 30)) && onAddWikiPageRequest) {
    onAddWikiPageRequest();
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Text("Wiki Pages:");
  ImGui::Spacing();

  // Display wiki pages for current project
  if (wikiPages && !wikiPages->empty()) {
    // Iterates over wiki pages
    for (size_t i = 0; i < wikiPages->size(); ++i) {
      const auto &wikiPage = (*wikiPages)[i];
      if (wikiPage && wikiPage->getProject() == currentProject) {
        ImGui::BeginChild(("WikiPage##" + wikiPage->getTitle()).c_str(),
                          ImVec2(0, 80), true);

        // Handle wiki page click to view
        if (ImGui::Selectable(wikiPage->getTitle().c_str(), false,
                              ImGuiSelectableFlags_None, ImVec2(0, 25)) &&
            onWikiPageSelect) {
          onWikiPageSelect(static_cast<int>(i), currentProject);
        }

        // Shows truncated wiki page text (100 char max)
        std::string previewText = wikiPage->getContent();
        if (previewText.length() > 100) {
          previewText = previewText.substr(0, 100) + "...";
        }

        ImGui::TextWrapped("%s", previewText.c_str());

        ImGui::EndChild();
        ImGui::Spacing();
      }
    }
  } else {
    // Basic error handling
    ImGui::Text("No wiki pages found for this project");
  }
}

/*
 * Helper method to convert enum type to string representation
 */
std::string ProjectsView::projectTypeToString(ProjectType project) const {
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
