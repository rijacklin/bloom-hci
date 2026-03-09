#include "../../include/controllers/DataController.h"
#include <fstream>
#include <iostream>

DataController::DataController() {}

/*
 * Saves task to file (mock db functionality)
 */
bool DataController::saveTasks(
    const std::map<ProjectType, std::vector<std::unique_ptr<Task>>> &tasks) {
  std::ofstream file(TASKS_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    std::cout << "Error: Could not open file" << std::endl;
    return false;
  }

  // Iterate over tasks mapped to projects
  for (const auto &project : tasks) {
    std::string projectName = projectTypeToString(project.first);

    // TOML-like format for project names
    file << "[" << projectName << "]\n";

    // Iterate over each task
    for (const auto &task : project.second) {
      // Structure for each task in file
      file << "TITLE:" << task->getTitle() << "\n";
      file << "ASSIGNED:" << task->getAssignedTo() << "\n";
      file << "DESC:" << task->getDescription() << "\n";
      file << "---\n";
    }

    // Write new line to end of file
    file << "\n";
  }

  // Close file and return
  file.close();
  return true;
}

/*
 * Loads tasks from file (mock db functionality)
 */
std::map<ProjectType, std::vector<std::unique_ptr<Task>>>
DataController::loadTasks() {
  // Create map to store associated tasks with projects
  std::map<ProjectType, std::vector<std::unique_ptr<Task>>> tasks;

  // Initialize empty vectors for each project to hold tasks
  tasks[ProjectType::DEPLOY] = std::vector<std::unique_ptr<Task>>();
  tasks[ProjectType::FLOW] = std::vector<std::unique_ptr<Task>>();
  tasks[ProjectType::BLOOM] = std::vector<std::unique_ptr<Task>>();

  std::ifstream file(TASKS_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    // Just write a message to console signifying missing task file
    std::cout << "No existing tasks file found. Starting with empty task list."
              << std::endl;
    return tasks;
  }

  std::string line;
  ProjectType currentProject = ProjectType::NONE;
  std::string title, assignedTo, description;
  bool hasTitle = false;

  // Iterate over lines in file
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    // Check for TOML-like structure
    if (line.front() == '[' && line.back() == ']') {
      // Store project name in string representation
      std::string projectName = line.substr(1, line.length() - 2);

      // Use helper function to get enum representation from that string
      currentProject = stringToProjectType(projectName);
      continue;
    }

    // Check for end of task structure
    if (line == "---") {
      // "Create" task for task list (stub functionality) if exists in file
      if (hasTitle && currentProject != ProjectType::NONE) {
        auto task = std::make_unique<Task>(title, assignedTo, description,
                                           currentProject);
        tasks[currentProject].push_back(std::move(task));
      }

      title = assignedTo = description = "";
      hasTitle = false;
      continue;
    }

    // Assign data to fields for "created" task
    if (line.substr(0, 6) == "TITLE:") {
      title = line.substr(6);
      hasTitle = true;
    } else if (line.substr(0, 9) == "ASSIGNED:") {
      assignedTo = line.substr(9);
    } else if (line.substr(0, 5) == "DESC:") {
      description = line.substr(5);
    }
  }

  // Close file and return mapping of tasks
  file.close();
  return tasks;
}

/*
 * Saves taskcards to file (mock db functionality)
 */
bool DataController::saveTaskCards(
    const std::map<ProjectType, std::vector<std::unique_ptr<TaskCard>>>
        &taskCards) {
  std::ofstream file(TASKCARDS_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    std::cout << "Error: Could not open file" << std::endl;
    return false;
  }

  // Iterate over taskcards mapped to projects
  for (const auto &project : taskCards) {
    std::string projectName = projectTypeToString(project.first);

    // TOML-like format for project names
    file << "[" << projectName << "]\n";

    // Iterate over each taskcard
    for (const auto &taskCard : project.second) {
      // Structure for each task in file
      file << "TITLE:" << taskCard->getTitle() << "\n";
      file << "ASSIGNED:" << taskCard->getAssignedTo() << "\n";
      file << "STORYPTS:" << taskCard->getStoryPoints() << "\n";
      file << "---\n";
    }

    // Write new line to end of file
    file << "\n";
  }

  // Close file and return
  file.close();
  return true;
}

/*
 * Loads taskcards from file (mock db functionality)
 */
std::map<ProjectType, std::vector<std::unique_ptr<TaskCard>>>
DataController::loadTaskCards() {
  // Create map to store associated taskcards with projects
  std::map<ProjectType, std::vector<std::unique_ptr<TaskCard>>> taskCards;

  // Initialize empty vectors for each project to hold task cards
  taskCards[ProjectType::DEPLOY] = std::vector<std::unique_ptr<TaskCard>>();
  taskCards[ProjectType::FLOW] = std::vector<std::unique_ptr<TaskCard>>();
  taskCards[ProjectType::BLOOM] = std::vector<std::unique_ptr<TaskCard>>();

  std::ifstream file(TASKCARDS_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    // Writes message to console signifying missing taskcard file
    std::cout << "No existing task cards file found. Starting with empty task "
                 "card list."
              << std::endl;
    return taskCards;
  }

  std::string line;
  ProjectType currentProject = ProjectType::NONE;
  std::string title, assignedTo;
  int storyPoints = 0;
  bool hasTitle = false;

  // Iterate over lines in file
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    // Check for TOML-like structure
    if (line.front() == '[' && line.back() == ']') {
      // Store project name in string representation
      std::string projectName = line.substr(1, line.length() - 2);

      // Use helper function to get enum representation from that string
      currentProject = stringToProjectType(projectName);

      continue;
    }

    // Check for end of taskcard structure
    if (line == "---") {
      // "Create" task for task list (stub functionality) if exists in file
      if (hasTitle && currentProject != ProjectType::NONE) {
        auto taskCard = std::make_unique<TaskCard>(title, assignedTo,
                                                   storyPoints, currentProject);
        taskCards[currentProject].push_back(std::move(taskCard));
      }
      title = assignedTo = "";
      storyPoints = 0;
      hasTitle = false;
      continue;
    }

    // Assign data to fields for "created" taskcard
    if (line.substr(0, 6) == "TITLE:") {
      title = line.substr(6);
      hasTitle = true;
    } else if (line.substr(0, 9) == "ASSIGNED:") {
      assignedTo = line.substr(9);
    } else if (line.substr(0, 9) == "STORYPTS:") {
      storyPoints = std::stoi(line.substr(9));
    }
  }

  // Close file and return mapping of taskcards
  file.close();
  return taskCards;
}

/*
 * Saves wiki pages to file (mock db functionality)
 */
bool DataController::saveWikiPages(
    const std::map<ProjectType, std::vector<std::unique_ptr<WikiPage>>>
        &wikiPages) {
  std::ofstream file(WIKIPAGES_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    std::cout << "Error: Could not open file" << std::endl;
    return false;
  }

  // Iterate over wiki pages mapped to projects
  for (const auto &project : wikiPages) {
    std::string projectName = projectTypeToString(project.first);

    // TOML-like format for project names
    file << "[" << projectName << "]\n";

    // Iterate over each wiki page
    for (const auto &page : project.second) {
      // Structure for each task in file
      file << "TITLE:" << page->getTitle() << "\n";
      file << "TEXT:" << page->getContent() << "\n";
      file << "---\n";
    }

    // Write new line to end of file
    file << "\n";
  }

  // Close file and return
  file.close();
  return true;
}

/*
 * Loads wiki pages from file (mock db functionality)
 */
std::map<ProjectType, std::vector<std::unique_ptr<WikiPage>>>
DataController::loadWikiPages() {
  // Create map to store associated wiki pages with projects
  std::map<ProjectType, std::vector<std::unique_ptr<WikiPage>>> wikiPages;

  // Initialize empty vectors for each project to hold wiki pages
  wikiPages[ProjectType::DEPLOY] = std::vector<std::unique_ptr<WikiPage>>();
  wikiPages[ProjectType::FLOW] = std::vector<std::unique_ptr<WikiPage>>();
  wikiPages[ProjectType::BLOOM] = std::vector<std::unique_ptr<WikiPage>>();

  std::ifstream file(WIKIPAGES_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    // Writes message to console signifying missing wiki pages file
    std::cout << "No existing wiki pages file found. Starting with empty wiki "
                 "page list."
              << std::endl;
    return wikiPages;
  }

  std::string line;
  ProjectType currentProject = ProjectType::NONE;
  std::string title, content;
  bool hasTitle = false, readingText = false;

  // iterate over lines in file
  while (std::getline(file, line)) {
    if (line.empty() && !readingText)
      continue;

    // Check for TOML-like structure
    if (line.front() == '[' && line.back() == ']') {
      // Store project name in string representation
      std::string projectName = line.substr(1, line.length() - 2);

      // Use helper function to get enum representation from that string
      currentProject = stringToProjectType(projectName);

      readingText = false;
      continue;
    }

    // Check for end of taskcard structure
    if (line == "---") {
      if (hasTitle && currentProject != ProjectType::NONE) {
        // "Create" wiki page for wiki list (stub functionality) if exists in
        // file
        auto wikiPage =
            std::make_unique<WikiPage>(title, content, currentProject);
        wikiPages[currentProject].push_back(std::move(wikiPage));
      }
      title = content = "";
      hasTitle = readingText = false;
      continue;
    }

    // Assign data to fields for "created" taskcard
    if (line.substr(0, 6) == "TITLE:") {
      title = line.substr(6);
      hasTitle = true;
      readingText = false;
    } else if (line.substr(0, 5) == "TEXT:") {
      content = line.substr(5);
      readingText = true;
    } else if (readingText) {
      content += "\n" + line;
    }
  }

  // Close file and return mapping of wiki pages
  file.close();
  return wikiPages;
}

/*
 * Saves authentication data (username/pw) to file (mock db functionality)
 */
bool DataController::saveAuthData(const std::string &data) {
  std::ofstream file(AUTH_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    std::cout << "Error: Could not open file" << std::endl;
    return false;
  }

  // Write auth data to file (stub functionality)
  file << data << std::endl;

  // Close file and return
  file.close();
  return true;
}

/*
 * Loads authentication data from file (mock db functionality)
 */
std::string DataController::loadAuthData() {
  std::ifstream file(AUTH_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    std::cout << "Error: Could not open file" << std::endl;
    return nullptr;
  }

  std::string data;
  std::getline(file, data);

  // Close file and return
  file.close();
  return data;
}

/*
 * Loads notifications from file (mock db functionality)
 */
std::vector<std::unique_ptr<Notification>> DataController::loadNotifications() {
  // Create vector of notifications
  std::vector<std::unique_ptr<Notification>> notifications;

  std::ifstream file(NOTIFICATIONS_FILE);

  // Basic file error handling
  if (!file.is_open()) {
    // write to console for missing notifications file
    std::cout << "No existing notifications file found. Starting with empty "
                 "notification list."
              << std::endl;
    return notifications;
  }

  std::string line;
  std::string title, text;
  bool isRead = false;
  bool hasTitle = false;
  int taskIndex = -1;
  ProjectType relatedProject = ProjectType::NONE;

  // Iterate over lines in file
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    // Check for end of task structure
    if (line == "---") {
      // "Create" task for task list (stub functionality) if exists in file
      if (hasTitle) {
        auto notification = std::make_unique<Notification>(
            title, text, isRead, taskIndex, relatedProject);
        notifications.push_back(std::move(notification));
      }

      title = text = "";
      isRead = false;
      hasTitle = false;
      taskIndex = -1;
      relatedProject = ProjectType::NONE;
      continue;
    }

    // Assign data to fields for "created" notification
    if (line.substr(0, 6) == "TITLE:") {
      title = line.substr(6);
      hasTitle = true;
    } else if (line.substr(0, 5) == "READ:") {
      std::string read = line.substr(5);
      isRead = (read == "true");
    } else if (line.substr(0, 5) == "TEXT:") {
      text = line.substr(5);
    } else if (line.substr(0, 10) == "TASKINDEX:") {
      // For associating notification with task (shortcut)
      taskIndex = std::stoi(line.substr(10));
    } else if (line.substr(0, 8) == "PROJECT:") {
      std::string projectStr = line.substr(8);
      relatedProject = Task::stringToProjectType(projectStr);
    }
  }

  // Close file and return
  file.close();
  return notifications;
}

/*
 * Helper method to convert enum type to string representation
 */
std::string DataController::projectTypeToString(ProjectType project) {
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

/*
 * Helper method to convert project string back to enum type
 */
ProjectType DataController::stringToProjectType(const std::string &projectStr) {
  if (projectStr == "DEPLOY")
    return ProjectType::DEPLOY;
  if (projectStr == "FLOW")
    return ProjectType::FLOW;
  if (projectStr == "BLOOM")
    return ProjectType::BLOOM;
  return ProjectType::NONE;
}
