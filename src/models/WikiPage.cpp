#include "../../include/models/WikiPage.h"
#include <chrono>
#include <ctime>

WikiPage::WikiPage()
    : title(""), content(""), lastModified(""), project(ProjectType::NONE) {
  updateTimeStamp();
}

WikiPage::WikiPage(const std::string &title, const std::string &content,
                   ProjectType project)
    : title(title), content(content), project(project) {
  updateTimeStamp();
}

/*
 * Helper method to get title
 */
const std::string &WikiPage::getTitle() const { return title; }

/*
 * Helper method to get content
 */
const std::string &WikiPage::getContent() const { return content; }

/*
 * Helper method to get time last modified
 */
const std::string &WikiPage::getLastModified() const { return lastModified; }

/*
 * Helper method to get a project instance
 */
ProjectType WikiPage::getProject() const { return project; }

/*
 * Sets title of wiki page
 */
void WikiPage::setTitle(const std::string &title) {
  this->title = title;
  updateTimeStamp();
}

/*
 * Sets content of wiki page
 */
void WikiPage::setContent(const std::string &content) {
  this->content = content;
  updateTimeStamp();
}

/*
 * Sets associated project
 */
void WikiPage::setProject(ProjectType project) { this->project = project; }

/*
 * Helper method to get truncated preview text
 */
std::string WikiPage::getPreviewText(size_t maxLength) const {
  if (content.length() <= maxLength) {
    return content;
  }
  return content.substr(0, maxLength) + "...";
}

/*
 * Helper method to set current time stamp
 */
void WikiPage::updateTimeStamp() {
  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);
  std::string timeStr = std::ctime(&time_t);

  // remove newline from timestring
  if (!timeStr.empty() && timeStr.back() == '\n') {
    timeStr.pop_back();
  }

  this->lastModified = timeStr;
}
