#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
  std::string username;
  std::string password;
  bool isFirstTimeUser;

public:
  User();
  User(const std::string &username);

  const std::string &getUsername() const;
  bool getIsFirstTimeUser() const;

  void setUsername(const std::string &username);
  void setPassword(const std::string &password);
  void setIsFirstTimeUser(bool isFirstTimeUser);

  bool authenticatePassword(const std::string &password) const;
  void updatePassword(const std::string &newPassword);
};

#endif // User.h
