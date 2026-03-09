#include "../../include/views/SetPasswordView.h"
#include <cstring>

SetPasswordView::SetPasswordView() : BaseView() {
  memset(newPassword, 0, sizeof(newPassword));
  memset(verifyPassword, 0, sizeof(verifyPassword));
}

/*
 * Renders view to mock the functionality of user changing temp password on
 * first login
 */
void SetPasswordView::render() {
  ImVec2 windowSize(500, 300);
  centerWindow(windowSize);

  ImGui::Begin("Set New Password", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoCollapse);

  ImGui::Text("Welcome! Please set a new password you will use to log in");
  ImGui::Separator();
  ImGui::Spacing();

  // New password input
  createPasswordInput("New Password:", newPassword, sizeof(newPassword), 130);
  ImGui::Spacing();

  // Verify password input
  createPasswordInput("Verify Password:", verifyPassword,
                      sizeof(verifyPassword), 130);
  ImGui::Spacing();
  ImGui::Spacing();

  // Basic checks for validity (length > 0) and matching
  bool passwordsMatch = doPasswordsMatch();

  // Ensure both are > 0 and match
  if (strlen(newPassword) > 0 && strlen(verifyPassword) > 0 &&
      !passwordsMatch) {
    ImGui::PushStyleColor(ImGuiCol_Text,
                          ImVec4(1.0f, 0.3f, 0.3f, 1.0f)); // Red text
    ImGui::Text("Passwords do not match!");
    ImGui::PopStyleColor();
    ImGui::Spacing();
  }

  // Center buttons
  float buttonWidth = 100;
  float spacing = 15;
  float totalWidth = buttonWidth * 2 + spacing;
  ImGui::SetCursorPosX((windowSize.x - totalWidth) * 0.5f);

  // Only make Create button clickable if passwords are valid
  if (createButton("Create", ImVec2(buttonWidth, 30))) {
    if (onPasswordSet) {
      onPasswordSet(std::string(newPassword), std::string(verifyPassword));
    }
  }

  ImGui::SameLine(0, spacing);

  // Create back button
  if (createButton("Back", ImVec2(buttonWidth, 30))) {
    if (onBackRequest) {
      onBackRequest();
    }
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void SetPasswordView::setOnPasswordSet(
    std::function<void(const std::string &, const std::string &)> callback) {
  onPasswordSet = callback;
}

void SetPasswordView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

/*
 * Helper method to clear password input forms
 */
void SetPasswordView::clearForm() {
  memset(newPassword, 0, sizeof(newPassword));
  memset(verifyPassword, 0, sizeof(verifyPassword));
}

/*
 * Helper method to check if two passwords match
 */
bool SetPasswordView::doPasswordsMatch() const {
  return strlen(newPassword) > 0 && strlen(verifyPassword) > 0 &&
         strcmp(newPassword, verifyPassword) == 0;
}
