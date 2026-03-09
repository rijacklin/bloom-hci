#include "../../include/models/Notification.h"
#include <chrono>
#include <ctime>

Notification::Notification()
    : title(""), text(""), isRead(false), taskIndex(-1),
      relatedProject(ProjectType::NONE) {
  generateTimeStamp();
}

Notification::Notification(const std::string &title, const std::string &text,
                           bool isRead, int taskIndex,
                           ProjectType relatedProject)
    : title(title), text(text), isRead(isRead), taskIndex(taskIndex),
      relatedProject(relatedProject) {
  generateTimeStamp();
}

/*
 * Helper method to get title
 */
const std::string &Notification::getTitle() const { return title; }

/*
 * Helper method to get notification text
 */
const std::string &Notification::getText() const { return text; }

/*
 * Helper method to check if notification is read
 */
bool Notification::getIsRead() const { return isRead; }

/*
 * Helper method to get notification timestamp
 */
const std::string &Notification::getTimeStamp() const { return timeStamp; }

/*
 * Helper method to get associated task
 */
int Notification::getTaskIndex() const { return taskIndex; }

/*
 * Helper method to get associated project
 */
ProjectType Notification::getRelatedProject() const { return relatedProject; }

/*
 * Sets notification title
 */
void Notification::setTitle(const std::string &title) { this->title = title; }

/*
 * Sets notification text
 */
void Notification::setText(const std::string &text) { this->text = text; }

/*
 * Sets notification read status
 */
void Notification::setIsRead(bool read) { this->isRead = read; }

/*
 * Sets notification's associated task index
 */
void Notification::setTaskIndex(int taskIndex) { this->taskIndex = taskIndex; }

/*
 * Sets notification's associated project
 */
void Notification::setRelatedProject(ProjectType relatedProject) {
  this->relatedProject = relatedProject;
}

/*
 * Helper method to mark notification as read
 */
void Notification::markAsRead() { this->isRead = true; }

/*
 * Helper method to mark notification as unread
 */
void Notification::markAsUnread() { this->isRead = false; }

/*
 * Helper method to generate timestamp for notification
 */
void Notification::generateTimeStamp() {
  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);
  std::string timeStr = std::ctime(&time_t);

  // remove newline from timestring
  if (!timeStr.empty() && timeStr.back() == '\n') {
    timeStr.pop_back();
  }

  this->timeStamp = timeStr;
}
