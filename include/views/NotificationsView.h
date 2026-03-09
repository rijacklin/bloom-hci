#ifndef NOTIFICATIONSVIEW_H
#define NOTIFICATIONSVIEW_H

#include "BaseView.h"
#include "../models/Notification.h"
#include "../models/Task.h"
#include <functional>
#include <vector>
#include <memory>

class NotificationsView : public BaseView {
private:
    ProjectType currentProject;
    
    // Callback functions for user actions
    std::function<void(ProjectType)> onProjectSelect;
    std::function<void()> onBackRequest;
    std::function<void()> onExitRequest;
    std::function<void(int)> onNotificationClick;
    
    // Data display
    const std::vector<std::unique_ptr<Notification>>* notifications;
    
public:
    NotificationsView();
    ~NotificationsView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnProjectSelect(std::function<void(ProjectType)> callback);
    void setOnBackRequest(std::function<void()> callback);
    void setOnExitRequest(std::function<void()> callback);
    void setOnNotificationClick(std::function<void(int)> callback);
    
    // Set data
    void setCurrentProject(ProjectType project);
    void setNotifications(const std::vector<std::unique_ptr<Notification>>* notifications);
    
private:
    void renderNotificationsMenu();
    void renderNotificationsList();
    std::string projectTypeToString(ProjectType project) const;
};

#endif // NotificationsView.h
