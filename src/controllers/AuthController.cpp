#include "../../include/controllers/AuthController.h"
#include <fstream>

AuthController::AuthController() : currentUser(nullptr) {}

/*
 * Logs user in (basic stub functionality)
 */
bool AuthController::login(const std::string &username,
                           const std::string &password) {
  // Basic error check
  if (username.empty() || password.empty())
    return false;

  // Verify credentials against data/auth.txt
  if (verifyCredentials(username, password)) {
    currentUser = std::make_unique<User>(username);
    currentUser->setIsFirstTimeUser(false);
    return true;
  }

  return false;
}

/*
 * Update user temp password (basic stub functionality)
 */
bool AuthController::setNewPassword(const std::string &username,
                                    const std::string &newPassword,
                                    const std::string &verifyPassword) {
  // Basic check to see whether the same data entered in both fields
  if (!validatePasswordMatch(newPassword, verifyPassword))
    return false;

  currentUser->updatePassword(newPassword);

  // Update password in data/auth.txt
  std::ifstream file("data/auth.txt");
  std::string fileContent;
  std::string line;
  bool userFound = false;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      if (line.substr(0, 9) == "USERNAME:" && line.substr(9) == username) {
        fileContent += line + "\n";
        userFound = true;
        // Replace user's temp password
        if (std::getline(file, line) && line.substr(0, 9) == "PASSWORD:") {
          fileContent += "PASSWORD:" + newPassword + "\n";
        }
        // update temp password flag for future log-ins
        if (std::getline(file, line) && line.substr(0, 7) == "TEMPPW:") {
          fileContent += "TEMPPW:false\n";
        } else {
          fileContent += line + "\n";
        }
      } else {
        fileContent += line + "\n";
      }
    }
    file.close();

    // Write back to file if user was found
    if (userFound) {
      std::ofstream outFile("data/auth.txt");
      if (outFile.is_open()) {
        outFile << fileContent;
        outFile.close();
      }
    }
  }

  return true;
}

/*
 * Stub logout functionality. Doesn't actually do anything
 */
void AuthController::logout() {
  // Log out user...
}

/*
 * Helper method to check if first time user (for temp password change flow)
 */
bool AuthController::isFirstTimeUser() const {
  if (!currentUser)
    return true;

  std::string username = currentUser->getUsername();
  std::ifstream file("data/auth.txt");
  if (!file.is_open()) {
    return true;
  }

  std::string line;
  bool usernameFound = false;

  while (std::getline(file, line)) {
    if (line.empty() || line == "---") {
      usernameFound = false;
      continue;
    }

    if (line.substr(0, 9) == "USERNAME:" && line.substr(9) == username) {
      usernameFound = true;
    } else if (line.substr(0, 7) == "TEMPPW:" && usernameFound) {
      return line.substr(7) == "true";
    }
  }

  return true;
}

/*
 * Helper method to get username
 */
const std::string &AuthController::getCurrentUsername() const {
  static const std::string empty = "";
  return currentUser ? currentUser->getUsername() : empty;
}

/*
 * Helper method to check if passwords match
 */
bool AuthController::validatePasswordMatch(
    const std::string &password, const std::string &verifyPassword) const {
  return !password.empty() && !verifyPassword.empty() &&
         password == verifyPassword;
}

bool AuthController::verifyCredentials(const std::string &username,
                                       const std::string &password) const {
  std::ifstream file("data/auth.txt");
  if (!file.is_open()) {
    return false;
  }

  std::string line;
  std::string currentUsername, currentPassword;
  bool usernameFound = false;

  while (std::getline(file, line)) {
    if (line.empty() || line == "---") {
      // Reset for next user block or skip empty lines
      if (usernameFound && currentPassword == password) {
        return true;
      }
      currentUsername.clear();
      currentPassword.clear();
      usernameFound = false;
      continue;
    }

    if (line.substr(0, 9) == "USERNAME:") {
      currentUsername = line.substr(9);
      usernameFound = (currentUsername == username);
    } else if (line.substr(0, 9) == "PASSWORD:" && usernameFound) {
      currentPassword = line.substr(9);
    }
  }

  // Check the last user block if file doesn't end with separator
  if (usernameFound && currentPassword == password) {
    return true;
  }

  return false;
}
