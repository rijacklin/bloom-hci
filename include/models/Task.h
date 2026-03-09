#ifndef TASK_H
#define TASK_H

#include "Comment.h"
#include <string>
#include <vector>

enum class ProjectType { NONE, DEPLOY, FLOW, BLOOM };

class Task {
private:
  std::string title;
  std::string assignedTo;
  std::string description;
  std::vector<Comment> comments;
  ProjectType project;

public:
  Task();
  Task(const std::string &title, const std::string &assignedTo,
       const std::string &description, ProjectType project = ProjectType::NONE);

  ~Task() = default;

  const std::string &getTitle() const;
  const std::string &getAssignedTo() const;
  const std::string &getDescription() const;
  const std::vector<Comment> &getComments() const;
  ProjectType getProject() const;

  void setTitle(const std::string &title);
  void setAssignedTo(const std::string &assignedTo);
  void setDescription(const std::string &description);
  void setProject(ProjectType project);

  void addComment(const Comment &comment);
  int getCommentCount() const;

  static std::string projectTypeToString(ProjectType project);
  static ProjectType stringToProjectType(const std::string &projectStr);
};

#endif // Task.h
