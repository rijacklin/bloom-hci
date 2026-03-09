#include "../../include/controllers/TaskController.h"
#include "../../include/controllers/DataController.h"

TaskController::TaskController() { initializeProjectMaps(); }

/*
 * Initializes vectors of tasks for project-specific mappings
 */
void TaskController::initializeProjectMaps() {
  projectTasks[ProjectType::DEPLOY] = std::vector<std::unique_ptr<Task>>();
  projectTasks[ProjectType::FLOW] = std::vector<std::unique_ptr<Task>>();
  projectTasks[ProjectType::BLOOM] = std::vector<std::unique_ptr<Task>>();
}

/*
 * Creates a task
 */
bool TaskController::createTask(const std::string &title,
                                const std::string &assignedTo,
                                const std::string &description,
                                ProjectType project) {
  if (!isValidTaskData(title, assignedTo))
    return false;

  auto task = std::make_unique<Task>(title, assignedTo, description, project);
  projectTasks[project].push_back(std::move(task));

  return true;
}

/*
 * Retrieves vector of tasks for project, otherwise empty vector
 */
const std::vector<std::unique_ptr<Task>> &
TaskController::getTasksForProject(ProjectType project) const {
  static const std::vector<std::unique_ptr<Task>> emptyVector;

  auto it = projectTasks.find(project);
  if (it != projectTasks.end())
    return it->second;

  return emptyVector;
}

/*
 * Retrieves an instance of a task
 */
Task *TaskController::getTask(int taskIndex, ProjectType project) {
  if (!isValidTaskIndex(taskIndex, project))
    return nullptr;
  return projectTasks[project][taskIndex].get();
}

/*
 * Returns number of tasks for project
 */
int TaskController::getTaskCount(ProjectType project) const {
  auto it = projectTasks.find(project);
  if (it != projectTasks.end()) {
    return static_cast<int>(it->second.size());
  }

  return 0;
}

/*
 * Adds comment to task
 */
bool TaskController::addCommentToTask(int taskIndex, ProjectType project,
                                      const std::string &commentText,
                                      const std::string &author) {
  if (!isValidTaskIndex(taskIndex, project)) {
    return false;
  }

  Comment comment(author, commentText, "");
  comment.generateTimeStamp();

  projectTasks[project][taskIndex]->addComment(comment);
  return true;
}

/*
 * Checks if task index is valid
 */
bool TaskController::isValidTaskIndex(int taskIndex,
                                      ProjectType project) const {
  auto it = projectTasks.find(project);
  if (it != projectTasks.end()) {
    return taskIndex >= 0 && taskIndex < static_cast<int>(it->second.size());
  }

  return false;
}

/*
 * Ensure task data is valid and return it
 */
bool TaskController::isValidTaskData(const std::string &title,
                                     const std::string &assignedTo) const {
  return !title.empty() && !assignedTo.empty() && title.length() <= 100 &&
         assignedTo.length() <= 50;
}

/*
 * Loads list of tasks
 */
void TaskController::loadTasks() {
  DataController dataController;
  projectTasks = dataController.loadTasks();
}

/*
 * Saves list of tasks
 */
void TaskController::saveTasks() {
  DataController dataController;
  dataController.saveTasks(projectTasks);
}
