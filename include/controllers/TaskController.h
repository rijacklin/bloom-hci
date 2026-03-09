#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include "../models/Comment.h"
#include "../models/Task.h"
#include <map>
#include <memory>
#include <vector>

class TaskController {
private:
  std::map<ProjectType, std::vector<std::unique_ptr<Task>>> projectTasks;
  void initializeProjectMaps();

public:
  TaskController();
  ~TaskController() = default;

  bool createTask(const std::string &title, const std::string &assignedTo,
                  const std::string &description, ProjectType project);

  const std::vector<std::unique_ptr<Task>> &
  getTasksForProject(ProjectType project) const;
  Task *getTask(int taskIndex, ProjectType project);
  int getTaskCount(ProjectType project) const;

  bool addCommentToTask(int taskIndex, ProjectType project,
                        const std::string &commentText,
                        const std::string &author);
  bool isValidTaskIndex(int taskIndex, ProjectType project) const;
  bool isValidTaskData(const std::string &title,
                       const std::string &assignedTo) const;
  void loadTasks();
  void saveTasks();
};

#endif // TaskController.h
