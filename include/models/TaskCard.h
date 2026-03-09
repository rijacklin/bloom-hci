#ifndef TASKCARD_H
#define TASKCARD_H

#include "Task.h"
#include <string>

class TaskCard {
private:
  std::string title;
  std::string assignedTo;
  int storyPoints;
  ProjectType project;

public:
  TaskCard();
  TaskCard(const std::string &title, const std::string &assignedTo,
           int storyPoints, ProjectType project = ProjectType::NONE);

  ~TaskCard() = default;

  const std::string &getTitle() const;
  const std::string &getAssignedTo() const;
  int getStoryPoints() const;
  ProjectType getProject() const;

  void setTitle(const std::string &title);
  void setAssignedTo(const std::string &assignedTo);
  void setStoryPoints(int points);
  void setProject(ProjectType project);

  bool isValidStoryPoints() const;
  float calculateSprintContribution(int totalSprintPoints) const;
};

#endif // TaskCard.h
