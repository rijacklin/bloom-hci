#include "../../include/controllers/TaskCardController.h"
#include "../../include/controllers/DataController.h"

TaskCardController::TaskCardController() { initializeProjectMaps(); }

/*
 * Initializes vectors of taskcards for project-specific mappings
 */
void TaskCardController::initializeProjectMaps() {
  sprintTaskCards[ProjectType::DEPLOY] =
      std::vector<std::unique_ptr<TaskCard>>();
  sprintTaskCards[ProjectType::FLOW] = std::vector<std::unique_ptr<TaskCard>>();
  sprintTaskCards[ProjectType::BLOOM] =
      std::vector<std::unique_ptr<TaskCard>>();
}

/*
 * Creates a taskcard
 */
bool TaskCardController::createTaskCard(const std::string &title,
                                        const std::string &assignedTo,
                                        int storyPoints, ProjectType project) {
  if (!isValidTaskCardData(title, assignedTo, storyPoints))
    return false;

  auto taskCard =
      std::make_unique<TaskCard>(title, assignedTo, storyPoints, project);
  sprintTaskCards[project].push_back(std::move(taskCard));

  return true;
}

/*
 * Retrieves vector of taskcards for project, otherwise emtpy vector
 */
const std::vector<std::unique_ptr<TaskCard>> &
TaskCardController::getTaskCardsForProject(ProjectType project) const {
  static const std::vector<std::unique_ptr<TaskCard>> emptyVector;

  auto it = sprintTaskCards.find(project);
  if (it != sprintTaskCards.end())
    return it->second;

  return emptyVector;
}

/*
 * Retrieves an instance of a taskcard
 */
TaskCard *TaskCardController::getTaskCard(int cardIndex, ProjectType project) {
  if (!isValidTaskCardIndex(cardIndex, project))
    return nullptr;
  return sprintTaskCards[project][cardIndex].get();
}

/*
 * Returns number of taskcards for project
 */
int TaskCardController::getTaskCardCount(ProjectType project) const {
  auto it = sprintTaskCards.find(project);
  if (it != sprintTaskCards.end()) {
    return static_cast<int>(it->second.size());
  }

  return 0;
}

/*
 * Calculates and returns sum of all taskcard story pts for project
 */
int TaskCardController::getTotalStoryPointsForProject(
    ProjectType project) const {
  int totalPoints = 0;

  auto it = sprintTaskCards.find(project);
  if (it != sprintTaskCards.end()) {
    for (const auto &card : it->second) {
      totalPoints += card->getStoryPoints();
    }
  }

  return totalPoints;
}

/*
 * Calculates and returns taskcard's story pt contribution to projec sprint
 */
float TaskCardController::getTaskCardContribution(int cardIndex,
                                                  ProjectType project) const {
  if (!isValidTaskCardIndex(cardIndex, project))
    return 0.0f;

  int totalPoints = getTotalStoryPointsForProject(project);
  if (totalPoints == 0)
    return 0.0f;

  int cardPoints = sprintTaskCards.at(project)[cardIndex]->getStoryPoints();
  return static_cast<float>(cardPoints) / static_cast<float>(totalPoints) *
         100.0f;
}

/*
 * Checks if taskcard index is valid
 */
bool TaskCardController::isValidTaskCardIndex(int cardIndex,
                                              ProjectType project) const {
  auto it = sprintTaskCards.find(project);
  if (it != sprintTaskCards.end()) {
    return cardIndex >= 0 && cardIndex < static_cast<int>(it->second.size());
  }

  return false;
}

/*
 * Ensure taskcard data is valid and return it
 */
bool TaskCardController::isValidTaskCardData(const std::string &title,
                                             const std::string &assignedTo,
                                             int storyPoints) const {
  return !title.empty() && !assignedTo.empty() && storyPoints > 0 &&
         storyPoints <= 100 && title.length() <= 100 &&
         assignedTo.length() <= 50;
}

/*
 * Loads list of taskcards
 */
void TaskCardController::loadTaskCards() {
  DataController dataController;
  sprintTaskCards = dataController.loadTaskCards();
}

/*
 * Saves list of taskcards
 */
void TaskCardController::saveTaskCards() {
  DataController dataController;
  dataController.saveTaskCards(sprintTaskCards);
}
