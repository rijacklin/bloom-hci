#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include "../models/Notification.h"
#include "../models/Task.h"
#include "../models/TaskCard.h"
#include "../models/WikiPage.h"
#include <map>
#include <memory>
#include <vector>

class DataController {
private:
  // Declares text files to replicate basic db function
  const std::string TASKS_FILE = "data/tasks.txt";
  const std::string TASKCARDS_FILE = "data/taskcards.txt";
  const std::string WIKIPAGES_FILE = "data/wikipages.txt";
  const std::string NOTIFICATIONS_FILE = "data/notifications.txt";
  const std::string AUTH_FILE = "data/auth.txt";

  std::string projectTypeToString(ProjectType project);
  ProjectType stringToProjectType(const std::string &projectString);

public:
  DataController();
  ~DataController() = default;

  bool saveTasks(
      const std::map<ProjectType, std::vector<std::unique_ptr<Task>>> &tasks);
  std::map<ProjectType, std::vector<std::unique_ptr<Task>>> loadTasks();
  bool saveTaskCards(
      const std::map<ProjectType, std::vector<std::unique_ptr<TaskCard>>>
          &taskCards);
  std::map<ProjectType, std::vector<std::unique_ptr<TaskCard>>> loadTaskCards();
  bool saveWikiPages(
      const std::map<ProjectType, std::vector<std::unique_ptr<WikiPage>>>
          &wikiPages);
  std::map<ProjectType, std::vector<std::unique_ptr<WikiPage>>> loadWikiPages();
  bool saveAuthData(const std::string &data);
  std::string loadAuthData();
  std::vector<std::unique_ptr<Notification>> loadNotifications();
};

#endif // DataController.h
