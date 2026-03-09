#include "../../include/controllers/NotificationController.h"

NotificationController::NotificationController() {}

/*
 * Creates a notification (from file/mock db)
 */
bool NotificationController::createNotification(const std::string &title,
                                                const std::string &text) {
  // Basic checks
  if (title.empty() || text.empty())
    return false;
  if (title.length() > 100 || text.length() > 500)
    return false;

  auto notification = std::make_unique<Notification>(title, text);
  notifications.push_back(std::move(notification));

  return true;
}

/*
 * Marks notification as read
 */
bool NotificationController::markNotificationAsRead(int notificationIndex) {
  if (!isValidNotificationIndex(notificationIndex))
    return false;

  notifications[notificationIndex]->markAsRead();
  return true;
}

/*
 * Returns vector containing all notifications
 */
const std::vector<std::unique_ptr<Notification>> &
NotificationController::getAllNotifications() const {
  return notifications;
}

/*
 * Returns a single notification
 */
Notification *NotificationController::getNotification(int notificationIndex) {
  if (!isValidNotificationIndex(notificationIndex))
    return nullptr;
  return notifications[notificationIndex].get();
}

/*
 * Check if notification at index exists
 */
bool NotificationController::isValidNotificationIndex(
    int notificationIndex) const {
  return notificationIndex >= 0 &&
         notificationIndex < static_cast<int>(notifications.size());
}

/*
 * Loads list of notifications
 */
void NotificationController::loadNotifications() {
  std::ifstream file("data/notifications.txt");

  // Basic file error handling
  if (!file.is_open()) {
    std::cout << "Error: Could not open file" << std::endl;
    return;
  }

  std::string line;
  std::string currentTitle;
  std::string currentText;
  bool isRead = false;
  bool hasTitle = false;
  int taskIndex = -1;
  ProjectType relatedProject = ProjectType::NONE;

  // Iterate over lines in file
  while (std::getline(file, line)) {
    // Skip empty lines
    if (line.empty())
      continue;

    // Check for TOML-like format for project names
    if (line.front() == '[' && line.back() == ']') {
      continue;
    }

    // Check for end of notification structure
    if (line == "---") {
      if (hasTitle) {
        // "Create" notification  (stub functionality) if exists in file
        auto notification = std::make_unique<Notification>(
            currentTitle, currentText, isRead, taskIndex, relatedProject);
        notifications.push_back(std::move(notification));
      }
      currentTitle.clear();
      currentText.clear();
      isRead = false;
      hasTitle = false;
      taskIndex = -1;
      relatedProject = ProjectType::NONE;
      continue;
    }

    // Assign data to fields for "created" notification
    if (line.substr(0, 6) == "TITLE:") {
      currentTitle = line.substr(6);
      hasTitle = true;
    } else if (line.substr(0, 5) == "READ:") {
      std::string readStatus = line.substr(5);
      isRead = (readStatus == "true");
    } else if (line.substr(0, 5) == "TEXT:") {
      currentText = line.substr(5);
    } else if (line.substr(0, 10) == "TASKINDEX:") {
      taskIndex = std::stoi(line.substr(10));
    } else if (line.substr(0, 8) == "PROJECT:") {
      std::string projectStr = line.substr(8);
      relatedProject = Task::stringToProjectType(projectStr);
    }
  }

  // Close file
  file.close();
}
