#ifndef AUTH_H
#define AUTH_H

#include "../models/User.h"
#include <memory>

class AuthController {
private:
  std::unique_ptr<User> currentUser;
  bool verifyCredentials(const std::string &username,
                         const std::string &password) const;

public:
  AuthController();
  ~AuthController() = default;

  bool login(const std::string &username, const std::string &password);
  bool setNewPassword(const std::string &username,
                      const std::string &newPassword,
                      const std::string &verifyPassword);
  void logout();
  bool isFirstTimeUser() const;
  const std::string &getCurrentUsername() const;
  bool validatePasswordMatch(const std::string &password,
                             const std::string &verifyPassword) const;
};

#endif // Auth.h
