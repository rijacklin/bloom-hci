#ifndef APP_H
#define APP_H

// Import Controller files
#include "controllers/AnalyticsController.h"
#include "controllers/AuthController.h"
#include "controllers/DataController.h"
#include "controllers/NotificationController.h"
#include "controllers/TaskCardController.h"
#include "controllers/TaskController.h"
#include "controllers/WikiPageController.h"

// Import View files
#include "views/AddTaskCardView.h"
#include "views/AddTaskView.h"
#include "views/AddWikiPageView.h"
#include "views/AnalyticsView.h"
#include "views/LoginView.h"
#include "views/NotificationsView.h"
#include "views/ProjectsView.h"
#include "views/SetPasswordView.h"
#include "views/TaskCardView.h"
#include "views/TaskView.h"
#include "views/WelcomeView.h"
#include "views/WikiPageView.h"
#include <memory>

class App {
private:
  // Required for GLUT backend
  static App *instance;

  // Declare safe pointers to controllers
  std::unique_ptr<AuthController> authController;
  std::unique_ptr<AnalyticsController> analyticsController;
  std::unique_ptr<DataController> dataController;
  std::unique_ptr<NotificationController> notificationController;
  std::unique_ptr<TaskController> taskController;
  std::unique_ptr<TaskCardController> taskCardController;
  std::unique_ptr<WikiPageController> wikiPageController;

  // Declare safe pointers to views
  std::unique_ptr<LoginView> loginView;
  std::unique_ptr<SetPasswordView> setPasswordView;
  std::unique_ptr<WelcomeView> welcomeView;
  std::unique_ptr<ProjectsView> projectsView;
  std::unique_ptr<NotificationsView> notificationsView;
  std::unique_ptr<AnalyticsView> analyticsView;
  std::unique_ptr<AddTaskView> addTaskView;
  std::unique_ptr<TaskView> taskView;
  std::unique_ptr<AddTaskCardView> addTaskCardView;
  std::unique_ptr<TaskCardView> taskCardView;
  std::unique_ptr<AddWikiPageView> addWikiPageView;
  std::unique_ptr<WikiPageView> wikiPageView;

  // App State
  Screen currentScreen;
  ProjectType currentProject;
  TaskViewMode currentViewMode;

  // DearImGui/OpenGL State
  bool isInitialized;

  // Method declarations
  void initializeControllers();
  void initializeViews();
  void setupViewCallBacks();
  void loadAppData();

  // Requierd GLUT backend methods
  bool initializeGLUTBackend(int argc, char **arvg);
  void cleanupGraphics();
  static void mainLoopStep();

public:
  App();
  ~App();

  bool initialize(int argc, char **arvg);
  void run();
  void shutdown();

  // Screen helper functions
  void switchToScreen(Screen screen);
  void renderCurrentScreen();

  // Callbacks
  void handleLogin(const std::string &username, const std::string &password);
  void handleSetPassword(const std::string &newPassword,
                         const std::string &verifyPassword);
  void handleLogout();
  void handleExit();
  void handleSelectProject(ProjectType project);
  void handleChangeViewMode(TaskViewMode taskMode);
  void handleNavigateToTask(int taskIndex, ProjectType project);
};

#endif // App.h
