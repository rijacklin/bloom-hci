#include "../../include/views/WelcomeView.h"

WelcomeView::WelcomeView() : BaseView() { loggedInUser = ""; }

/*
 * Renders main welcome view after login
 */
void WelcomeView::render() {
  ImGuiIO &io = getIO();

  // Left side menu
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y), ImGuiCond_Always);

  if (ImGui::Begin("Menu", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderMenu();
  }

  ImGui::End();

  // Right side content
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 200, io.DisplaySize.y),
                           ImGuiCond_Always);

  if (ImGui::Begin("Main Content", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderMainContent();
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void WelcomeView::setOnProjectsRequest(std::function<void()> callback) {
  onProjectsRequest = callback;
}

void WelcomeView::setOnNotificationsRequest(std::function<void()> callback) {
  onNotificationsRequest = callback;
}

void WelcomeView::setOnLogoutRequest(std::function<void()> callback) {
  onLogoutRequest = callback;
}

void WelcomeView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

void WelcomeView::setLoggedInUser(const std::string &username) {
  loggedInUser = username;
}

/*
 * Declares contents of left side menu for rendering
 */
void WelcomeView::renderMenu() {
  ImGui::Text("Navigation");
  ImGui::Separator();

  if (ImGui::Button("Projects", ImVec2(180, 40)) && onProjectsRequest) {
    onProjectsRequest();
  }

  if (ImGui::Button("Notifications", ImVec2(180, 40)) &&
      onNotificationsRequest) {
    onNotificationsRequest();
  }

  // Bottom buttons
  ImGuiIO &io = getIO();
  ImGui::SetCursorPosY(io.DisplaySize.y - 90);
  ImGui::Separator();

  if (ImGui::Button("Logout", ImVec2(180, 30)) && onLogoutRequest) {
    onLogoutRequest();
  }

  // Exit button - removed extra spacing
  if (ImGui::Button("Exit", ImVec2(180, 30)) && onExitRequest) {
    onExitRequest();
  }
}

/*
 * Declares contents of right main content window for rendering
 */
void WelcomeView::renderMainContent() {
  ImGuiIO &io = getIO();

  // Center the Welcome message
  ImGui::SetCursorPosY(io.DisplaySize.y * 0.4f);

  std::string welcomeMsg = "Welcome, " + loggedInUser + "!";
  float textWidth = ImGui::CalcTextSize(welcomeMsg.c_str()).x;
  ImGui::SetCursorPosX((io.DisplaySize.x - 200 - textWidth) * 0.5f);

  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 20));
  ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Use default font
  ImGui::Text("%s", welcomeMsg.c_str());
  ImGui::PopFont();
  ImGui::PopStyleVar();

  ImGui::SetCursorPosX((io.DisplaySize.x - 200 - 300) * 0.5f);
  ImGui::Text("Please select an option from the menu on the left.");
}
