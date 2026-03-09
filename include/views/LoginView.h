#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include "BaseView.h"
#include <functional>

class LoginView : public BaseView {
private:
  char username[128];
  char password[128];

  // Error handling
  bool showLoginError;
  std::string errorMessage;

  std::function<void(const std::string &, const std::string &)> onLoginAttempt;
  std::function<void()> onExitRequest;

public:
  LoginView();
  ~LoginView() = default;

  // override render function from base
  void render() override;

  void setOnLoginAttempt(
      std::function<void(const std::string &, const std::string &)> callback);
  void setOnExitRequest(std::function<void()> callback);

  // error handling
  void showError(const std::string &message);

  // clear data
  void clearForm();
};

#endif // LoginView.h
