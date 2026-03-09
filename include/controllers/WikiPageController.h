#ifndef WIKIPAGECONTROLLER_H
#define WIKIPAGECONTROLLER_H

#include "../models/WikiPage.h"
#include <map>
#include <memory>
#include <vector>

class WikiPageController {
private:
  std::map<ProjectType, std::vector<std::unique_ptr<WikiPage>>>
      projectWikiPages;
  void initializeProjectMaps();

public:
  WikiPageController();
  ~WikiPageController() = default;

  bool createWikiPage(const std::string &title, const std::string &content,
                      ProjectType project);
  const std::vector<std::unique_ptr<WikiPage>> &
  getWikiPagesForProject(ProjectType project) const;
  WikiPage *getWikiPage(int pageIndex, ProjectType project);
  int getWikiPageCount(ProjectType project) const;

  bool isValidWikiPageIndex(int pageIndex, ProjectType project) const;
  bool isValidWikiPageData(const std::string &title,
                           const std::string &content) const;

  void loadWikiPages();
  void saveWikiPages();
};

#endif // WikiPageController.h
