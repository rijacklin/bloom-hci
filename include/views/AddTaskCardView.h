#ifndef ADDTASKCARDVIEW_H
#define ADDTASKCARDVIEW_H

#include "BaseView.h"
#include "models/TaskCard.h"
#include <cstring>
#include <functional>

class AddTaskCardView : public BaseView {
private:
  ProjectType currentProject;
  char newTaskCardTitle[256];
  int newTaskCardStoryPts;
  int selectedSprintTaskUserIndex;

  // Error handling
  bool showTitleError;
  std::string errorMessage;

  // Users array
  static constexpr const char *users[7] = {"Richard", "John",  "Anna",  "Frank",
                                           "Michael", "Sally", "Joseph"};

  // Callback functions for user actions
  std::function<void(const std::string &, const std::string &, int,
                     ProjectType)>
      onTaskCardCreate;
  std::function<void()> onBackRequest;

public:
  AddTaskCardView();
  ~AddTaskCardView() = default;

  // Override from BaseView
  void render() override;

  // Setters for callbacks
  void
  setOnTaskCardCreate(std::function<void(const std::string &,
                                         const std::string &, int, ProjectType)>
                          callback);
  void setOnBackRequest(std::function<void()> callback);

  // Set data
  void setCurrentProject(ProjectType project);
  void clearForm();

private:
  std::string projectTypeToString(ProjectType project) const;
};

#endif // ADDTASKCARDVIEW_H
