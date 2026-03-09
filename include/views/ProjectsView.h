#ifndef PROJECTSVIEW_H
#define PROJECTSVIEW_H

#include "BaseView.h"
#include "../models/Task.h"
#include "../models/TaskCard.h"
#include "../models/WikiPage.h"
#include <functional>
#include <vector>
#include <memory>

class ProjectsView : public BaseView {
private:
    ProjectType currentProject;
    TaskViewMode viewMode;
    
    // Callback functions for user actions
    std::function<void(ProjectType)> onProjectSelect;
    std::function<void()> onAddTaskRequest;
    std::function<void()> onAddTaskCardRequest;
    std::function<void(int, ProjectType)> onTaskSelect;
    std::function<void(int, ProjectType)> onTaskCardSelect;
    std::function<void()> onAnalyticsRequest;
    std::function<void()> onWikiRequest;
    std::function<void()> onAddWikiPageRequest;
    std::function<void(int, ProjectType)> onWikiPageSelect;
    std::function<void(TaskViewMode)> onViewModeChange;
    std::function<void()> onBackRequest;
    std::function<void()> onExitRequest;
    
    // Data display
    const std::vector<std::unique_ptr<Task>>* tasks;
    const std::vector<std::unique_ptr<TaskCard>>* taskCards;
    const std::vector<std::unique_ptr<WikiPage>>* wikiPages;
    
public:
    ProjectsView();
    ~ProjectsView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnProjectSelect(std::function<void(ProjectType)> callback);
    void setOnAddTaskRequest(std::function<void()> callback);
    void setOnAddTaskCardRequest(std::function<void()> callback);
    void setOnTaskSelect(std::function<void(int, ProjectType)> callback);
    void setOnTaskCardSelect(std::function<void(int, ProjectType)> callback);
    void setOnAnalyticsRequest(std::function<void()> callback);
    void setOnWikiRequest(std::function<void()> callback);
    void setOnAddWikiPageRequest(std::function<void()> callback);
    void setOnWikiPageSelect(std::function<void(int, ProjectType)> callback);
    void setOnViewModeChange(std::function<void(TaskViewMode)> callback);
    void setOnBackRequest(std::function<void()> callback);
    void setOnExitRequest(std::function<void()> callback);
    
    // Set data
    void setCurrentProject(ProjectType project);
    void setViewMode(TaskViewMode mode);
    void setTasks(const std::vector<std::unique_ptr<Task>>* tasks);
    void setTaskCards(const std::vector<std::unique_ptr<TaskCard>>* taskCards);
    void setWikiPages(const std::vector<std::unique_ptr<WikiPage>>* wikiPages);
    
private:
    void renderProjectMenu();
    void renderProjectContent();
    void renderProjectButtons();
    void renderTaskList();
    void renderSprintList();
    void renderWikiList();
    int calculateTotalStoryPoints() const;
    std::string projectTypeToString(ProjectType project) const;
};

#endif // ProjectsView.h
