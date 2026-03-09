#ifndef WIKIPAGE_H
#define WIKIPAGE_H

#include "Task.h"
#include <string>

class WikiPage {
private:
  std::string title;
  std::string content;
  std::string lastModified;
  ProjectType project;

public:
  WikiPage();
  WikiPage(const std::string &title, const std::string &content,
           ProjectType project = ProjectType::NONE);

  const std::string &getTitle() const;
  const std::string &getContent() const;
  const std::string &getLastModified() const;
  ProjectType getProject() const;

  void setTitle(const std::string &title);
  void setContent(const std::string &content);
  void setProject(ProjectType project);

  std::string getPreviewText(size_t maxLength = 100) const;
  void updateTimeStamp();
};

#endif // WikiPage.h
