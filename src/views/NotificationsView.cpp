#include "../../include/views/NotificationsView.h"

NotificationsView::NotificationsView() : BaseView() {
  currentProject = ProjectType::NONE;
  notifications = nullptr;
}

/*
 * Renders notifications list
 */
void NotificationsView::render() {
  ImGuiIO &io = BaseView::getIO();

  // Left side menu
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y), ImGuiCond_Always);

  if (ImGui::Begin("Notifications Menu", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoScrollbar)) {
    renderNotificationsMenu();
  }

  ImGui::End();

  // Right side content
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 200, io.DisplaySize.y),
                           ImGuiCond_Always);

  if (ImGui::Begin("Notifications Content", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderNotificationsList();
  }
  ImGui::End();
}

/*
 * Event handlers
 */
void NotificationsView::setOnProjectSelect(
    std::function<void(ProjectType)> callback) {
  onProjectSelect = callback;
}

void NotificationsView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void NotificationsView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

void NotificationsView::setOnNotificationClick(
    std::function<void(int)> callback) {
  onNotificationClick = callback;
}

/*
 * Helper method to set current project
 */
void NotificationsView::setCurrentProject(ProjectType project) {
  currentProject = project;
}

/*
 * Helper method to set project notifications
 */
void NotificationsView::setNotifications(
    const std::vector<std::unique_ptr<Notification>> *notifications) {
  this->notifications = notifications;
}

/*
 * Declares contents of left side menu for rendering
 */
void NotificationsView::renderNotificationsMenu() {
  ImGui::Text("MENU");
  ImGui::Separator();

  // Bottom buttons
  ImGuiIO &io = BaseView::getIO();
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
 * Declares contents of right main notifications window for rendering
 */
void NotificationsView::renderNotificationsList() {
  ImGui::Text("NOTIFICATIONS");
  ImGui::Separator();
  ImGui::Spacing();

  // Displays user's notifications (very basic functionality, not actually tied
  // to user)
  if (notifications && !notifications->empty()) {
    int notificationIndex = 0;
    // iterate over notifications
    for (const auto &notification : *notifications) {
      if (notification) {
        ImGui::BeginChild(("notification##" + notification->getTitle()).c_str(),
                          ImVec2(0, 80), true);

        // Displays an orange circle for unread notifications (UI enhancement)
        if (!notification->getIsRead()) {
          ImDrawList *draw_list = ImGui::GetWindowDrawList();
          ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
          float circle_radius = 4.0f;
          ImVec2 circle_center(cursor_pos.x + circle_radius + 5,
                               cursor_pos.y + 12);
          ImU32 orange_color = IM_COL32(255, 165, 0, 255); // Orange color
          draw_list->AddCircleFilled(circle_center, circle_radius,
                                     orange_color);

          // Move cursor to make room for the circle
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20);
        }

        // Basic error check
        if (ImGui::Selectable(notification->getTitle().c_str(), false,
                              ImGuiSelectableFlags_None, ImVec2(0, 25))) {
          // Mark clicked notification as read (remove orange circle)
          if (onNotificationClick) {
            onNotificationClick(notificationIndex);
          }
        }

        // notification text
        ImGui::Text("%s", notification->getText().c_str());

        ImGui::EndChild();
        ImGui::Spacing();
      }

      notificationIndex++;
    }
  } else {
    ImGui::Text("No notifications.");
  }
}

/*
 * Helper method to convert enum type to string representation
 */
std::string NotificationsView::projectTypeToString(ProjectType project) const {
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
