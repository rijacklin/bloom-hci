#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "Task.h"
#include <string>

class Notification {
private:
  std::string title;
  std::string text;
  bool isRead;
  std::string timeStamp;
  int taskIndex;
  ProjectType relatedProject;

public:
  Notification();
  Notification(const std::string &title, const std::string &text,
               bool isRead = false, int taskIndex = -1,
               ProjectType relatedProject = ProjectType::NONE);

  ~Notification() = default;

  const std::string &getTitle() const;
  const std::string &getText() const;
  bool getIsRead() const;
  const std::string &getTimeStamp() const;
  int getTaskIndex() const;
  ProjectType getRelatedProject() const;

  void setTitle(const std::string &title);
  void setText(const std::string &text);
  void setIsRead(bool read);
  void setTaskIndex(int taskIndex);
  void setRelatedProject(ProjectType relatedProject);
  void markAsRead();
  void markAsUnread();
  void generateTimeStamp();
};

#endif // Notification.h
