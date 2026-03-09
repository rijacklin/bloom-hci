#include "../../include/models/Task.h"

Task::Task()
    : title(""), assignedTo(""), description(""), project(ProjectType::NONE) {}
Task::Task(const std::string &title, const std::string &assignedTo,
           const std::string &description, ProjectType project)
    : title(title), assignedTo(assignedTo), description(description),
      project(project) {}

/*
 * Helper method to get title
 */
const std::string &Task::getTitle() const { return title; }

/*
 * Helper method to get user assigned to task
 */
const std::string &Task::getAssignedTo() const { return assignedTo; }

/*
 * Helper method to get description
 */
const std::string &Task::getDescription() const { return description; }

/*
 * Helper method to get task comments
 */
const std::vector<Comment> &Task::getComments() const { return comments; }

/*
 * Helper method to get a project instance
 */
ProjectType Task::getProject() const { return project; }

/*
 * Sets title of task
 */
void Task::setTitle(const std::string &title) { this->title = title; }

/*
 * Assigns task to user (basically stub functionality)
 */
void Task::setAssignedTo(const std::string &assignedTo) {
  this->assignedTo = assignedTo;
}

/*
 * Sets task description
 */
void Task::setDescription(const std::string &description) {
  this->description = description;
}

/*
 * Sets associated project
 */
void Task::setProject(ProjectType project) { this->project = project; }

/*
 * Helper method to add a comment to a task
 */
void Task::addComment(const Comment &comment) { comments.push_back(comment); }

/*
 * Helper method to get count of comments on task
 */
int Task::getCommentCount() const { return static_cast<int>(comments.size()); }

/*
 * Helper method to convert enum type to string representation
 */
std::string Task::projectTypeToString(ProjectType project) {
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
 * Helper method to convert string back to enum type
 */
ProjectType Task::stringToProjectType(const std::string &projectStr) {
  if (projectStr == "DEPLOY")
    return ProjectType::DEPLOY;
  if (projectStr == "FLOW")
    return ProjectType::FLOW;
  if (projectStr == "BLOOM")
    return ProjectType::BLOOM;
  return ProjectType::NONE;
}
