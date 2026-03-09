#include "../../include/models/TaskCard.h"

TaskCard::TaskCard()
    : title(""), assignedTo(""), storyPoints(0), project(ProjectType::NONE) {}
TaskCard::TaskCard(const std::string &title, const std::string &assignedTo,
                   int storyPoints, ProjectType project)
    : title(title), assignedTo(assignedTo), storyPoints(storyPoints),
      project(project) {}

/*
 * Helper method to get title
 */
const std::string &TaskCard::getTitle() const { return title; }

/*
 * Helper method to get user assigned to taskcard
 */
const std::string &TaskCard::getAssignedTo() const { return assignedTo; }

/*
 * Helper method to get taskcard story points contribution
 */
int TaskCard::getStoryPoints() const { return storyPoints; }

/*
 * Helper method to get a project instance
 */
ProjectType TaskCard::getProject() const { return project; }

/*
 * Sets title of taskcard
 */
void TaskCard::setTitle(const std::string &title) { this->title = title; }

/*
 * Assigns taskcard to user (basically stub functionality)
 */
void TaskCard::setAssignedTo(const std::string &assignedTo) {
  this->assignedTo = assignedTo;
}

/*
 * Sets story points for taskcard
 */
void TaskCard::setStoryPoints(int points) {
  if (points >= 0) {
    this->storyPoints = points;
  }
}

/*
 * Sets associated project
 */
void TaskCard::setProject(ProjectType project) { this->project = project; }

/*
 * Helper method to check if story points > 0
 */
bool TaskCard::isValidStoryPoints() const { return storyPoints > 0; }

/*
 * Helper method to calculate total story point contribution form task card
 */
float TaskCard::calculateSprintContribution(int totalSprintPoints) const {
  if (totalSprintPoints <= 0)
    return 0.0f;
  return (static_cast<float>(storyPoints) /
          static_cast<float>(totalSprintPoints)) *
         100.0f;
}
