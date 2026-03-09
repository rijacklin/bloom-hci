#include "../../include/views/TaskView.h"
#include <ctime>

TaskView::TaskView() : BaseView() {
  currentTask = nullptr;
  currentTaskIndex = -1;
  currentProject = ProjectType::NONE;
  loggedInUser = "";
  memset(newCommentText, 0, sizeof(newCommentText));
}

/*
 * Renders single task screen
 */
void TaskView::render() {
  ImGuiIO &io = getIO();

  // Left side menu
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y), ImGuiCond_Always);

  if (ImGui::Begin("Task View Menu", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoScrollbar)) {
    renderTaskMenu();
  }

  ImGui::End();

  // Right side content
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 200, io.DisplaySize.y),
                           ImGuiCond_Always);

  if (ImGui::Begin("Task Details", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderTaskContent();
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void TaskView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void TaskView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

void TaskView::setOnCommentAdd(
    std::function<void(const std::string &, int, ProjectType)> callback) {
  onCommentAdd = callback;
}

/*
 * Helper method to set current task
 */
void TaskView::setCurrentTask(std::unique_ptr<Task> task, int index,
                              ProjectType project) {
  currentTask = std::move(task);
  currentTaskIndex = index;
  currentProject = project;
}

/*
 * Helper method to set currently logged in user (basic stub functionality)
 */
void TaskView::setLoggedInUser(const std::string &user) { loggedInUser = user; }

/*
 * Clears comment field
 */
void TaskView::clearCommentInput() {
  memset(newCommentText, 0, sizeof(newCommentText));
}

/*
 * Declares contents of left side menu for rendering
 */
void TaskView::renderTaskMenu() {
  ImGui::Text("MENU");
  ImGui::Separator();

  // Bottom buttons
  ImGuiIO &io = getIO();
  ImGui::SetCursorPosY(io.DisplaySize.y - 90);
  ImGui::Separator();

  if (ImGui::Button("<= Back to Tasks", ImVec2(180, 30)) && onBackRequest) {
    currentTask = nullptr;
    currentTaskIndex = -1;
    clearCommentInput();
    onBackRequest();
  }

  if (ImGui::Button("Exit", ImVec2(180, 30)) && onExitRequest) {
    onExitRequest();
  }
}

/*
 * Declares contents of right main content window for rendering
 */
void TaskView::renderTaskContent() {
  // Basic error checking before displaying task
  if (currentTask != nullptr) {
    // Title
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Text("Task: %s", currentTask->getTitle().c_str());
    ImGui::PopFont();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Assigned To
    ImGui::Text("Assigned To:");
    ImGui::SameLine(150);
    ImGui::Text("%s", currentTask->getAssignedTo().c_str());

    ImGui::Spacing();

    // Project
    ImGui::Text("Project:");
    ImGui::SameLine(150);
    std::string projectName = projectTypeToString(currentProject);
    ImGui::Text("%s", projectName.c_str());

    ImGui::Spacing();
    ImGui::Spacing();

    // Description
    ImGui::Text("Description:");
    ImGui::Separator();
    ImGui::Spacing();

    // scroll textbox for content
    ImGui::BeginChild("Description", ImVec2(0, 150), true,
                      ImGuiWindowFlags_AlwaysVerticalScrollbar);
    ImGui::TextWrapped("%s", currentTask->getDescription().c_str());
    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::Spacing();

    // Comments section (informal communication from assignment tasks)
    ImGui::Text("Comments:");
    ImGui::Separator();
    ImGui::Spacing();

    // Display existing comments
    const auto &comments = currentTask->getComments();
    if (comments.empty()) {
      ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f),
                         "No comments yet. Be the first to comment!");
    } else {
      // Comments display area
      ImGui::BeginChild("CommentsArea", ImVec2(0, 200), true,
                        ImGuiWindowFlags_AlwaysVerticalScrollbar);

      for (const auto &comment : comments) {
        // container for comment
        ImGui::BeginChild(
            ("Comment##" + comment.getAuthor() + comment.getTimeStamp())
                .c_str(),
            ImVec2(0, 60), true);

        // header
        ImGui::PushStyleColor(ImGuiCol_Text,
                              ImVec4(0.4f, 0.8f, 1.0f, 1.0f)); // Light blue
        ImGui::Text("%s", comment.getAuthor().c_str());
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text,
                              ImVec4(0.6f, 0.6f, 0.6f, 1.0f)); // Gray
        ImGui::Text("- %s", comment.getTimeStamp().c_str());
        ImGui::PopStyleColor();

        // comment
        ImGui::TextWrapped("%s", comment.getText().c_str());

        ImGui::EndChild();
        ImGui::Spacing();
      }

      ImGui::EndChild();
    }

    ImGui::Spacing();

    // New comment section
    ImGui::Text("Add Comment:");
    ImGui::InputTextMultiline("##newcomment", newCommentText,
                              sizeof(newCommentText), ImVec2(500, 80),
                              ImGuiInputTextFlags_AllowTabInput);

    ImGui::Spacing();

    if (ImGui::Button("Post Comment", ImVec2(120, 30))) {
      if (strlen(newCommentText) > 0 && onCommentAdd) {
        // Add the comment and clear the input
        onCommentAdd(std::string(newCommentText), currentTaskIndex,
                     currentProject);
        clearCommentInput();
      }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Action buttons
    if (ImGui::Button("Edit Task", ImVec2(100, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete Task", ImVec2(100, 30))) {
      // Stub functionatliy for now...
    }
  } else {
    // Display basic error state
    ImGui::Text("Error: No task selected");
  }
}

/*
 * Helper method to convert enum type to string representation
 */
std::string TaskView::projectTypeToString(ProjectType project) const {
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
