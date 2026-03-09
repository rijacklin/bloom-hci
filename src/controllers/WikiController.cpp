#include "../../include/controllers/DataController.h"
#include "../../include/controllers/WikiPageController.h"

WikiPageController::WikiPageController() { initializeProjectMaps(); }

/*
 * Initializes vectors of wiki pages for project-specific mappings
 */
void WikiPageController::initializeProjectMaps() {
  projectWikiPages[ProjectType::DEPLOY] =
      std::vector<std::unique_ptr<WikiPage>>();
  projectWikiPages[ProjectType::FLOW] =
      std::vector<std::unique_ptr<WikiPage>>();
  projectWikiPages[ProjectType::BLOOM] =
      std::vector<std::unique_ptr<WikiPage>>();
}

/*
 * Creates a wiki page
 */
bool WikiPageController::createWikiPage(const std::string &title,
                                        const std::string &content,
                                        ProjectType project) {
  if (!isValidWikiPageData(title, content))
    return false;

  auto wikiPage = std::make_unique<WikiPage>(title, content, project);
  projectWikiPages[project].push_back(std::move(wikiPage));

  return true;
}

/*
 * Returns wiki pages associated with project, otherwise empty vector
 */
const std::vector<std::unique_ptr<WikiPage>> &
WikiPageController::getWikiPagesForProject(ProjectType project) const {
  static const std::vector<std::unique_ptr<WikiPage>> emptyVector;

  auto it = projectWikiPages.find(project);
  if (it != projectWikiPages.end()) {
    return it->second;
  }

  return emptyVector;
}

WikiPage *WikiPageController::getWikiPage(int pageIndex, ProjectType project) {
  if (!isValidWikiPageIndex(pageIndex, project)) {
    return nullptr;
  }

  return projectWikiPages[project][pageIndex].get();
}

/*
 * Retrieves an instance of a wikipage
 */
int WikiPageController::getWikiPageCount(ProjectType project) const {
  auto it = projectWikiPages.find(project);
  if (it != projectWikiPages.end()) {
    return static_cast<int>(it->second.size());
  }

  return 0;
}

/*
 * Checks if wiki page index is valid
 */
bool WikiPageController::isValidWikiPageIndex(int pageIndex,
                                              ProjectType project) const {
  auto it = projectWikiPages.find(project);
  if (it != projectWikiPages.end()) {
    return pageIndex >= 0 && pageIndex < static_cast<int>(it->second.size());
  }

  return false;
}

/*
 * Ensure taskcard data is valid and return it
 */
bool WikiPageController::isValidWikiPageData(const std::string &title,
                                             const std::string &content) const {
  return !title.empty() && title.length() <= 200;
}

/*
 * Loads list of wiki pages
 */
void WikiPageController::loadWikiPages() {
  DataController dataController;
  projectWikiPages = dataController.loadWikiPages();
}

/*
 * Saves list of wiki pages
 */
void WikiPageController::saveWikiPages() {
  DataController dataController;
  dataController.saveWikiPages(projectWikiPages);
}
