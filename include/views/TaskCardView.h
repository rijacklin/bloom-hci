#ifndef TASKCARDVIEW_H
#define TASKCARDVIEW_H

#include "BaseView.h"
#include "../models/TaskCard.h"
#include <functional>
#include <memory>

class TaskCardView : public BaseView {
private:
    std::unique_ptr<TaskCard> currentTaskCard;
    int currentTaskCardIndex;
    ProjectType currentProject;
    
    // Callback functions for user actions
    std::function<void()> onBackRequest;
    std::function<void()> onExitRequest;
    std::function<int(ProjectType)> onCalculateTotalStoryPoints;
    
public:
    TaskCardView();
    ~TaskCardView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnBackRequest(std::function<void()> callback);
    void setOnExitRequest(std::function<void()> callback);
    void setOnCalculateTotalStoryPoints(std::function<int(ProjectType)> callback);
    
    // Set data
    void setCurrentTaskCard(std::unique_ptr<TaskCard> taskCard, int index, ProjectType project);
    
private:
    void renderTaskCardMenu();
    void renderTaskCardContent();
    std::string projectTypeToString(ProjectType project) const;
};

#endif // TASKCARDVIEW_H
