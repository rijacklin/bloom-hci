#ifndef TASKCARDCONTROLLER_H
#define TASKCARDCONTROLLER_H

#include "../models/TaskCard.h"
#include <map>
#include <memory>
#include <vector>

class TaskCardController {
private:
  std::map<ProjectType, std::vector<std::unique_ptr<TaskCard>>> sprintTaskCards;
  void initializeProjectMaps();

public:
  TaskCardController();
  ~TaskCardController() = default;

  bool createTaskCard(const std::string &title, const std::string &assignedTo,
                      int storyPoints, ProjectType project);
  const std::vector<std::unique_ptr<TaskCard>> &
  getTaskCardsForProject(ProjectType project) const;
  TaskCard *getTaskCard(int cardIndex, ProjectType project);
  int getTaskCardCount(ProjectType project) const;
  int getTotalStoryPointsForProject(ProjectType project) const;
  float getTaskCardContribution(int cardIndex, ProjectType project) const;
  bool isValidTaskCardIndex(int cardIndex, ProjectType project) const;
  bool isValidTaskCardData(const std::string &title,
                           const std::string &assignedTo,
                           int storyPoints) const;
  void loadTaskCards();
  void saveTaskCards();
};

#endif // TaskCardController.h
