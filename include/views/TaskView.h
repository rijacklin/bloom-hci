#ifndef TASKVIEW_H
#define TASKVIEW_H

#include "BaseView.h"
#include "../models/Task.h"
#include "../models/Comment.h"
#include <functional>
#include <memory>
#include <cstring>

class TaskView : public BaseView {
private:
    std::unique_ptr<Task> currentTask;
    int currentTaskIndex;
    ProjectType currentProject;
    std::string loggedInUser;
    char newCommentText[512];
    
    // Callback functions for user actions
    std::function<void()> onBackRequest;
    std::function<void()> onExitRequest;
    std::function<void(const std::string&, int, ProjectType)> onCommentAdd;
    
public:
    TaskView();
    ~TaskView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnBackRequest(std::function<void()> callback);
    void setOnExitRequest(std::function<void()> callback);
    void setOnCommentAdd(std::function<void(const std::string&, int, ProjectType)> callback);
    
    // Set data
    void setCurrentTask(std::unique_ptr<Task> task, int index, ProjectType project);
    void setLoggedInUser(const std::string& user);
    void clearCommentInput();
    
private:
    void renderTaskMenu();
    void renderTaskContent();
    std::string projectTypeToString(ProjectType project) const;
};

#endif // TaskView.h
