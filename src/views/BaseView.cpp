#include "../../include/views/BaseView.h"

BaseView::BaseView() : io(nullptr) {}

/*
 * Helper method to get reference to framework's I/O functionality
 */
ImGuiIO &BaseView::getIO() {
  if (!io)
    io = &ImGui::GetIO();
  return *io;
}

/*
 * Helper method to center a window in framework
 */
void BaseView::centerWindow(ImVec2 windowSize) {
  ImGuiIO &ioRef = getIO();
  ImVec2 windowPos((ioRef.DisplaySize.x - windowSize.x) * 0.5f,
                   (ioRef.DisplaySize.y - windowSize.y) * 0.5f);
  ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
  ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
}

/*
 * Helper method to create a menu layout in framework
 */
void BaseView::createMenuLayout(ImVec2 menuSize) {
  ImGuiIO &ioRef = getIO();
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(menuSize.x, ioRef.DisplaySize.y),
                           ImGuiCond_Always);
}

/*
 * Helper method to create a content layout in framework
 */
void BaseView::createContentLayout(ImVec2 menuSize) {
  ImGuiIO &ioRef = getIO();
  ImGui::SetNextWindowPos(ImVec2(menuSize.x, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(
      ImVec2(ioRef.DisplaySize.x - menuSize.x, ioRef.DisplaySize.y),
      ImGuiCond_Always);
}

/*
 * Helper method to create a button framework
 */
bool BaseView::createButton(const char *label, ImVec2 size) {
  return ImGui::Button(label, size);
}

/*
 * Helper method to create a cetnred button framework
 */
bool BaseView::createCenteredButton(const char *label, ImVec2 size,
                                    float windowWidth) {
  float buttonX = (windowWidth - size.x) * 0.5f;
  ImGui::SetCursorPosX(buttonX);
  return ImGui::Button(label, size);
}

/*
 * Helper method to create a text field in frameowork
 */
bool BaseView::createTextInput(const char *label, char *buffer,
                               size_t bufferSize, float labelWidth) {
  ImGui::Text("%s", label);
  ImGui::SameLine(labelWidth);
  ImGui::SetNextItemWidth(250);
  std::string inputId = "##" + std::string(label);
  return ImGui::InputText(inputId.c_str(), buffer, bufferSize,
                          ImGuiInputTextFlags_AllowTabInput);
}

/*
 * Helper method to create a password field in framework
 */
bool BaseView::createPasswordInput(const char *label, char *buffer,
                                   size_t bufferSize, float labelWidth) {
  ImGui::Text("%s", label);
  ImGui::SameLine(labelWidth);
  ImGui::SetNextItemWidth(250);
  std::string inputId = "##" + std::string(label);
  return ImGui::InputText(inputId.c_str(), buffer, bufferSize,
                          ImGuiInputTextFlags_Password |
                              ImGuiInputTextFlags_AllowTabInput);
}

/*
 * Helper method to create a multi-line field in framework
 */
bool BaseView::createMultilineInput(const char *label, char *buffer,
                                    size_t bufferSize, ImVec2 size) {
  ImGui::Text("%s", label);
  std::string inputId = "##" + std::string(label);
  return ImGui::InputTextMultiline(inputId.c_str(), buffer, bufferSize, size,
                                   ImGuiInputTextFlags_AllowTabInput);
}
