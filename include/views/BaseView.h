#ifndef BASEVIEW_H
#define BASEVIEW_H

#include "../utils.h"

enum class Screen {
  Login,
  SetPassword,
  Welcome,
  Projects,
  Notifications,
  Analytics,
  Wikis,
  AddTask,
  AddTaskCard,
  AddWikiPage,
  ViewTask,
  ViewTaskCard,
  ViewWikiPage
};

class BaseView {
protected:
  // pointer to I/O functionality from dearimgui
  ImGuiIO *io;

  // Helper method to get ImGui IO (lazy initialization)
  ImGuiIO &getIO();

public:
  BaseView();
  virtual ~BaseView() = default;

  // DearImGui helper method declarations
  virtual void render() = 0;
  void centerWindow(ImVec2 windowSize);
  void createMenuLayout(ImVec2 menuSize);
  void createContentLayout(ImVec2 menuSize);
  bool createButton(const char *label, ImVec2 size);
  bool createCenteredButton(const char *label, ImVec2 size, float windowWidth);
  bool createTextInput(const char *label, char *buffer, size_t bufferSize,
                       float labelWidth = 100.0f);
  bool createPasswordInput(const char *label, char *buffer, size_t bufferSize,
                           float labelWidth = 100.0f);
  bool createMultilineInput(const char *label, char *buffer, size_t bufferSize,
                            ImVec2 size);
};

#endif // BaseView.h
