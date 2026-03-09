#ifndef ADDWIKIPAGEVIEW_H
#define ADDWIKIPAGEVIEW_H

#include "BaseView.h"
#include "models/WikiPage.h"
#include <cstring>
#include <functional>

class AddWikiPageView : public BaseView {
private:
  ProjectType currentProject;
  char newWikiPageTitle[256];
  char newWikiPageText[512];

  // Error handling
  bool showTitleError;
  std::string errorMessage;

  // Callback functions for user actions
  std::function<void(const std::string &, const std::string &, ProjectType)>
      onWikiPageCreate;
  std::function<void()> onBackRequest;

public:
  AddWikiPageView();
  ~AddWikiPageView() = default;

  // Override from BaseView
  void render() override;

  // Setters for callbacks
  void setOnWikiPageCreate(
      std::function<void(const std::string &, const std::string &, ProjectType)>
          callback);
  void setOnBackRequest(std::function<void()> callback);

  // Set data
  void setCurrentProject(ProjectType project);
  void clearForm();

private:
  std::string projectTypeToString(ProjectType project) const;
};

#endif // ADDWIKIPAGEVIEW_H
