#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include "BaseView.h"
#include <functional>
#include <string>

class WelcomeView : public BaseView {
private:
    std::string loggedInUser;
    
    // Callback functions for user actions
    std::function<void()> onProjectsRequest;
    std::function<void()> onNotificationsRequest;
    std::function<void()> onLogoutRequest;
    std::function<void()> onExitRequest;
    
public:
    WelcomeView();
    ~WelcomeView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnProjectsRequest(std::function<void()> callback);
    void setOnNotificationsRequest(std::function<void()> callback);
    void setOnLogoutRequest(std::function<void()> callback);
    void setOnExitRequest(std::function<void()> callback);
    
    // Set user data
    void setLoggedInUser(const std::string& username);
    
private:
    void renderMenu();
    void renderMainContent();
};

#endif // WelcomeView.h
