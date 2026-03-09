#ifndef ADDTASKVIEW_H
#define ADDTASKVIEW_H

#include "BaseView.h"
#include "models/Task.h"
#include <functional>
#include <cstring>

class AddTaskView : public BaseView {
private:
    ProjectType currentProject;
    char newTaskTitle[256];
    char newTaskDescription[512];
    int selectedTaskUserIndex;
    
    // Error handling
    bool showTitleError;
    std::string errorMessage;
    
    // Users array
    static constexpr const char* users[7] = {"Richard", "John", "Anna", "Frank", "Michael", "Sally", "Joseph"};
    
    // Callback functions for user actions
    std::function<void(const std::string&, const std::string&, const std::string&, ProjectType)> onTaskCreate;
    std::function<void()> onBackRequest;
    
public:
    AddTaskView();
    ~AddTaskView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnTaskCreate(std::function<void(const std::string&, const std::string&, const std::string&, ProjectType)> callback);
    void setOnBackRequest(std::function<void()> callback);
    
    // Set data
    void setCurrentProject(ProjectType project);
    void clearForm();
    
private:
    std::string projectTypeToString(ProjectType project) const;
};

#endif // AddTaskView.h
