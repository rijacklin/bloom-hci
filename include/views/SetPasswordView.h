#ifndef SETPASSWORDVIEW_H
#define SETPASSWORDVIEW_H

#include "BaseView.h"
#include <functional>

class SetPasswordView : public BaseView {
private:
    char newPassword[128];
    char verifyPassword[128];
    
    // Callback functions for user actions
    std::function<void(const std::string&, const std::string&)> onPasswordSet;
    std::function<void()> onBackRequest;
    
public:
    SetPasswordView();
    ~SetPasswordView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnPasswordSet(std::function<void(const std::string&, const std::string&)> callback);
    void setOnBackRequest(std::function<void()> callback);
    
    // Clear form data
    void clearForm();
    
private:
    bool doPasswordsMatch() const;
};

#endif // SetPasswordView.h
