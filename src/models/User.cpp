#include "../../include/models/User.h"

User::User() : username(""), password(""), isFirstTimeUser(true) {}
User::User(const std::string &username)
    : username(username), password(""), isFirstTimeUser(true) {}

/*
 * Helper method to get username
 */
const std::string &User::getUsername() const { return username; }

/*
 * Helper method to check if first time user has logged in
 */
bool User::getIsFirstTimeUser() const { return isFirstTimeUser; }

/*
 * Sets username
 */
void User::setUsername(const std::string &username) {
  this->username = username;
}

/*
 * Sets password
 */
void User::setPassword(const std::string &password) {
  this->password = password;
}

/*
 * Sets firstime user status
 */
void User::setIsFirstTimeUser(bool isFirstTime) {
  this->isFirstTimeUser = isFirstTime;
}

/*
 * Helper method to authenticate password
 * NOTE: This is very barebones functionality for this course project, not to be
 * used in actual application.
 */
bool User::authenticatePassword(const std::string &password) const {
  return this->password == password;
}

/*
 * Helper method to "update" password
 * NOTE: This is very barebones functionality for this course project, not to be
 * used in actual application.
 */
void User::updatePassword(const std::string &newPassword) {
  this->isFirstTimeUser = false;
}
