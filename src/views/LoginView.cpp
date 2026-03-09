#include "../../include/views/LoginView.h"
#include <cstring>

LoginView::LoginView() : BaseView() {
  memset(username, 0, sizeof(username));
  memset(password, 0, sizeof(password));
  showLoginError = false;
  errorMessage = "";
}

/*
 * Renders initial login view
 */
void LoginView::render() {
  ImVec2 windowSize(400, 200);
  centerWindow(windowSize);

  ImGui::Begin("Login", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoCollapse);

  ImGui::Text("Please log in to continue");
  ImGui::Separator();
  ImGui::Spacing();

  // Username input
  if (showLoginError) {
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.2f, 0.2f, 0.3f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,
                          ImVec4(0.8f, 0.2f, 0.2f, 0.4f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                          ImVec4(0.8f, 0.2f, 0.2f, 0.5f));
  }

  createTextInput("Username:", username, sizeof(username));

  // Login error handling
  if (showLoginError) {
    ImGui::PopStyleColor(3);
  }

  ImGui::Spacing();

  // Password input
  if (showLoginError) {
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.2f, 0.2f, 0.3f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,
                          ImVec4(0.8f, 0.2f, 0.2f, 0.4f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                          ImVec4(0.8f, 0.2f, 0.2f, 0.5f));
  }

  createPasswordInput("Password:", password, sizeof(password));

  // Login error handling
  if (showLoginError) {
    ImGui::PopStyleColor(3);
  }

  ImGui::Spacing();

  // Display error message
  if (showLoginError && !errorMessage.empty()) {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
    ImGui::Text("%s", errorMessage.c_str());
    ImGui::PopStyleColor();
    ImGui::Spacing();
  }

  ImGui::Spacing();

  // Centre bottom buttons
  float buttonWidth = 100;
  float spacing = 15;
  float totalWidth = buttonWidth * 2 + spacing;
  ImGui::SetCursorPosX((windowSize.x - totalWidth) * 0.5f);

  if (createButton("Log In", ImVec2(buttonWidth, 30))) {
    if (onLoginAttempt) {
      onLoginAttempt(std::string(username), std::string(password));
    }
  }

  ImGui::SameLine(0, spacing);

  if (createButton("Exit", ImVec2(buttonWidth, 30))) {
    if (onExitRequest) {
      onExitRequest();
    }
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void LoginView::setOnLoginAttempt(
    std::function<void(const std::string &, const std::string &)> callback) {
  onLoginAttempt = callback;
}

void LoginView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

/*
 * Helper method to show login form error
 */
void LoginView::showError(const std::string &message) {
  showLoginError = true;
  errorMessage = message;
}

/*
 * Helper method to clear login form
 */
void LoginView::clearForm() {
  memset(username, 0, sizeof(username));
  memset(password, 0, sizeof(password));
  showLoginError = false;
  errorMessage = "";
}
