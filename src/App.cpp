#include "../include/App.h"
#include <cstdlib>
#include <iostream>

/*
 * Static member for GLUT callback
 */
App *App::instance = nullptr;

App::App()
    : currentScreen(Screen::Login), currentProject(ProjectType::NONE),
      currentViewMode(TaskViewMode::Tasks), isInitialized(false) {
  instance = this; // Set instance of GLUT to handle callbacks
}

App::~App() { shutdown(); }

/*
 * Initializes bloom application
 */
bool App::initialize(int argc, char **argv) {
  // Write message to console
  std::cout << "Initializing Bloom App..." << std::endl;

  // Initialize controllers and views
  initializeControllers();
  initializeViews();
  setupViewCallBacks();
  loadAppData();

  // Initialize graphics system
  if (!initializeGLUTBackend(argc, argv)) {
    // Basic error handling
    std::cout << "Failed to initialize GLUT" << std::endl;
    return false;
  }

  isInitialized = true;
  std::cout << "Application initialized successfully" << std::endl;

  return true;
}

/*
 * Point where Bloom runs
 */
void App::run() {
  // Basic check and error handling
  if (!isInitialized) {
    std::cout << "Application not initialized" << std::endl;
    return;
  }

  // Required for GLUT backend
  glutMainLoop();
}

/*
 * Properly exits Bloom application (to hopefully avoid mem leaks, etc)
 */
void App::shutdown() {
  if (isInitialized) {
    cleanupGraphics();
    isInitialized = false;
  }
}

/*
 * Helper method to switch application screen
 */
void App::switchToScreen(Screen screen) {
  // Set the current screen for the user
  currentScreen = screen;

  // Clear view-specific from data when switching
  switch (screen) {
  case Screen::Login:
    if (loginView)
      loginView->clearForm();
    break;
  case Screen::SetPassword:
    if (setPasswordView)
      setPasswordView->clearForm();
    break;
  case Screen::Analytics:
    if (analyticsView)
      analyticsView->clearForm();
    break;
  default:
    break;
  }
}

/*
 * Helper method to render screens
 */
void App::renderCurrentScreen() {
  switch (currentScreen) {
  case Screen::Login:
    if (loginView)
      loginView->render();
    break;
  case Screen::SetPassword:
    if (setPasswordView)
      setPasswordView->render();
    break;
  case Screen::Welcome:
    if (welcomeView)
      welcomeView->render();
    break;
  case Screen::Projects:
    // Projects screen is more complex than other screens, requiring additional
    // logic
    if (projectsView) {
      // Update project view with current data
      if (currentProject != ProjectType::NONE) {
        projectsView->setCurrentProject(currentProject);

        // Requires setting all data types before rendering
        projectsView->setTasks(
            &taskController->getTasksForProject(currentProject));
        projectsView->setTaskCards(
            &taskCardController->getTaskCardsForProject(currentProject));
        projectsView->setWikiPages(
            &wikiPageController->getWikiPagesForProject(currentProject));
      }
      projectsView->setViewMode(currentViewMode);
      projectsView->render();
    }
    break;
  case Screen::Notifications:
    if (notificationsView) {
      notificationsView->setCurrentProject(currentProject);

      // Handle notification loading before rendering
      notificationsView->setNotifications(
          &notificationController->getAllNotifications());
      notificationsView->render();
    }
    break;
  case Screen::Analytics:
    if (analyticsView) {
      analyticsView->setCurrentProject(currentProject);
      analyticsView->render();
    }
    break;
  case Screen::AddTask:
    if (addTaskView) {
      addTaskView->setCurrentProject(currentProject);
      addTaskView->render();
    }
    break;
  case Screen::ViewTask:
    if (taskView) {
      taskView->setLoggedInUser(authController->getCurrentUsername());
      taskView->render();
    }
    break;
  case Screen::Wikis:
    // Wiki screen is also more complex than other screens, requiring additional
    // logic
    if (projectsView) {
      if (currentProject != ProjectType::NONE) {
        projectsView->setCurrentProject(currentProject);

        // Requires setting all data types before rendering
        projectsView->setTasks(
            &taskController->getTasksForProject(currentProject));
        projectsView->setTaskCards(
            &taskCardController->getTaskCardsForProject(currentProject));
        projectsView->setWikiPages(
            &wikiPageController->getWikiPagesForProject(currentProject));
      }
      projectsView->setViewMode(TaskViewMode::Wiki);
      projectsView->render();
    }
    break;
  case Screen::AddTaskCard:
    if (addTaskCardView) {
      addTaskCardView->setCurrentProject(currentProject);
      addTaskCardView->render();
    }
    break;
  case Screen::ViewTaskCard:
    if (taskCardView) {
      taskCardView->render();
    }
    break;
  case Screen::AddWikiPage:
    if (addWikiPageView) {
      addWikiPageView->setCurrentProject(currentProject);
      addWikiPageView->render();
    }
    break;
  case Screen::ViewWikiPage:
    if (wikiPageView) {
      wikiPageView->render();
    }
    break;
  default:
    // Basic error handling for navigation edge case
    ImGui::Text("ERROR: NOT YET IMPLEMENTED");
    break;
  }
}

/*
 * Logs the user into the application
 */
void App::handleLogin(const std::string &username,
                      const std::string &password) {
  if (authController->login(username, password)) {
    // conditional branch to show the change temp password screen if first login
    if (authController->isFirstTimeUser()) {
      switchToScreen(Screen::SetPassword);
    } else {
      // if user already logged in before, direct them to login screen
      welcomeView->setLoggedInUser(authController->getCurrentUsername());
      switchToScreen(Screen::Welcome);
    }
  } else {
    // Show error message if authentication failed
    loginView->showError("Invalid username or password. Please try again.");
  }
}

/*
 * Handles changing user's temp password
 * NOTE: Very basic stub functionality, doesn't actually verify anything
 */
void App::handleSetPassword(const std::string &newPassword,
                            const std::string &verifyPassword) {
  if (authController->setNewPassword(authController->getCurrentUsername(),
                                     newPassword, verifyPassword)) {
    welcomeView->setLoggedInUser(authController->getCurrentUsername());

    // Direct user to welcome screen after simulating temp password change
    switchToScreen(Screen::Welcome);
  }
}

/*
 * Handles logging user out of application.
 * NOTE: Very basic stub fuctionality
 */
void App::handleLogout() {
  // This would properly handle logging user out in real application
  authController->logout();

  // Direct user to login screen
  switchToScreen(Screen::Login);
}

/*
 * Exits program using basic C++ exit (as is normally used with GLUT apps)
 */
void App::handleExit() { exit(0); }

/*
 * Selects a new project.
 */
void App::handleSelectProject(ProjectType project) {
  // Set the project passed in as current
  currentProject = project;

  // Direct user to projects screen
  switchToScreen(Screen::Projects);
}

/*
 * Helper method to switch context to task
 */
void App::handleNavigateToTask(int taskIndex, ProjectType project) {
  // Update the current project to the task's project
  currentProject = project;

  // Get the task and navigate to it
  Task *task = taskController->getTask(taskIndex, project);
  if (task != nullptr) {
    // Create a copy of the task for the view
    auto taskCopy = std::make_unique<Task>(*task);
    taskView->setCurrentTask(std::move(taskCopy), taskIndex, project);
    switchToScreen(Screen::ViewTask);
  }
}

/*
 * Helper method to switch task view mode
 */
void App::handleChangeViewMode(TaskViewMode mode) {
  // Update the current task view mode
  currentViewMode = mode;

  // This is necessary to prevent rendering glitch when navigation from wikis to
  // Tasks/Sprints on project screen
  if (currentScreen == Screen::Wikis &&
      (mode == TaskViewMode::Tasks || mode == TaskViewMode::Sprint)) {
    switchToScreen(Screen::Projects);
  }
}

/*
 * Helper method to initialize instances of controllers
 */
void App::initializeControllers() {
  dataController = std::make_unique<DataController>();
  authController = std::make_unique<AuthController>();
  taskController = std::make_unique<TaskController>();
  taskCardController = std::make_unique<TaskCardController>();
  wikiPageController = std::make_unique<WikiPageController>();
  notificationController = std::make_unique<NotificationController>();
  analyticsController = std::make_unique<AnalyticsController>(
      taskController.get(), taskCardController.get());
}

/*
 * Helper method to initialize instances of views
 */
void App::initializeViews() {
  loginView = std::make_unique<LoginView>();
  setPasswordView = std::make_unique<SetPasswordView>();
  welcomeView = std::make_unique<WelcomeView>();
  projectsView = std::make_unique<ProjectsView>();
  notificationsView = std::make_unique<NotificationsView>();
  analyticsView = std::make_unique<AnalyticsView>();
  addTaskView = std::make_unique<AddTaskView>();
  taskView = std::make_unique<TaskView>();
  addTaskCardView = std::make_unique<AddTaskCardView>();
  taskCardView = std::make_unique<TaskCardView>();
  addWikiPageView = std::make_unique<AddWikiPageView>();
  wikiPageView = std::make_unique<WikiPageView>();
}

/*
 * Event callbacks
 */
void App::setupViewCallBacks() {
  // Setup login view callbacks
  loginView->setOnLoginAttempt(
      [this](const std::string &username, const std::string &password) {
        handleLogin(username, password);
      });
  loginView->setOnExitRequest([this]() { handleExit(); });

  // Setup set password view callbacks
  setPasswordView->setOnPasswordSet([this](const std::string &newPassword,
                                           const std::string &verifyPassword) {
    handleSetPassword(newPassword, verifyPassword);
  });
  setPasswordView->setOnBackRequest(
      [this]() { switchToScreen(Screen::Login); });

  // Setup welcome view callbacks
  welcomeView->setOnProjectsRequest(
      [this]() { switchToScreen(Screen::Projects); });
  welcomeView->setOnNotificationsRequest(
      [this]() { switchToScreen(Screen::Notifications); });
  welcomeView->setOnLogoutRequest([this]() { handleLogout(); });
  welcomeView->setOnExitRequest([this]() { handleExit(); });

  // Setup projects view callbacks
  projectsView->setOnProjectSelect(
      [this](ProjectType project) { handleSelectProject(project); });
  projectsView->setOnAnalyticsRequest(
      [this]() { switchToScreen(Screen::Analytics); });
  projectsView->setOnTaskSelect([this](int taskIndex, ProjectType project) {
    // Set the selected task for viewing
    Task *task = taskController->getTask(taskIndex, project);
    if (task != nullptr) {
      // Create a copy of the task for the view
      auto taskCopy = std::make_unique<Task>(*task);
      taskView->setCurrentTask(std::move(taskCopy), taskIndex, project);
      switchToScreen(Screen::ViewTask);
    }
  });
  projectsView->setOnAddTaskRequest(
      [this]() { switchToScreen(Screen::AddTask); });
  projectsView->setOnTaskCardSelect(
      [this](int taskCardIndex, ProjectType project) {
        // Set the selected task card for viewing
        TaskCard *taskCard =
            taskCardController->getTaskCard(taskCardIndex, project);
        if (taskCard != nullptr) {
          // Create a copy of the task card for the view
          auto taskCardCopy = std::make_unique<TaskCard>(*taskCard);
          taskCardView->setCurrentTaskCard(std::move(taskCardCopy),
                                           taskCardIndex, project);
          switchToScreen(Screen::ViewTaskCard);
        }
      });
  projectsView->setOnAddTaskCardRequest([this]() {
    // Navigate to add task card screen
    switchToScreen(Screen::AddTaskCard);
  });
  projectsView->setOnWikiRequest([this]() {
    // Set view mode to wiki but stay on Projects screen
    handleChangeViewMode(TaskViewMode::Wiki);
  });
  projectsView->setOnAddWikiPageRequest([this]() {
    // Navigate to add wiki page screen
    switchToScreen(Screen::AddWikiPage);
  });
  projectsView->setOnWikiPageSelect(
      [this](int wikiPageIndex, ProjectType project) {
        // Set the selected wiki page for viewing
        WikiPage *wikiPage =
            wikiPageController->getWikiPage(wikiPageIndex, project);
        if (wikiPage != nullptr) {
          // Create a copy of the wiki page for the view
          auto wikiPageCopy = std::make_unique<WikiPage>(*wikiPage);
          wikiPageView->setCurrentWikiPage(std::move(wikiPageCopy),
                                           wikiPageIndex, project);
          switchToScreen(Screen::ViewWikiPage);
        }
      });
  projectsView->setOnViewModeChange(
      [this](TaskViewMode mode) { handleChangeViewMode(mode); });
  projectsView->setOnBackRequest([this]() { switchToScreen(Screen::Welcome); });
  projectsView->setOnExitRequest([this]() { handleExit(); });

  // Setup notifications view callbacks
  notificationsView->setOnProjectSelect(
      [this](ProjectType project) { handleSelectProject(project); });
  notificationsView->setOnBackRequest(
      [this]() { switchToScreen(Screen::Welcome); });
  notificationsView->setOnExitRequest([this]() { handleExit(); });
  notificationsView->setOnNotificationClick([this](int notificationIndex) {
    // Mark the notification as read
    notificationController->markNotificationAsRead(notificationIndex);

    // Get the notification to check if it references a task
    Notification *notification =
        notificationController->getNotification(notificationIndex);
    if (notification != nullptr) {
      std::cout << "Clicked notification: " << notification->getTitle()
                << std::endl;
      std::cout << "Task index: " << notification->getTaskIndex() << std::endl;
      std::cout << "Related project: "
                << static_cast<int>(notification->getRelatedProject())
                << std::endl;

      if (notification->getTaskIndex() >= 0 &&
          notification->getRelatedProject() != ProjectType::NONE) {
        std::cout << "Navigating to task..." << std::endl;
        // Navigate to the referenced task
        handleNavigateToTask(notification->getTaskIndex(),
                             notification->getRelatedProject());
      } else {
        std::cout << "No valid task reference found." << std::endl;
      }
    }
  });

  // Setup analytics view callbacks
  analyticsView->setOnProjectSelect(
      [this](ProjectType project) { handleSelectProject(project); });
  analyticsView->setOnBackRequest(
      [this]() { switchToScreen(Screen::Projects); });
  analyticsView->setOnExitRequest([this]() { handleExit(); });

  // Setup add task view callbacks
  addTaskView->setOnTaskCreate([this](const std::string &title,
                                      const std::string &assignedTo,
                                      const std::string &description,
                                      ProjectType project) {
    // Create and add new task
    if (taskController->createTask(title, assignedTo, description, project)) {
      // Successfully created task, save and go back to projects
      taskController->saveTasks();
      switchToScreen(Screen::Projects);
    }
  });
  addTaskView->setOnBackRequest([this]() { switchToScreen(Screen::Projects); });

  // Setup view task view callbacks
  taskView->setOnBackRequest([this]() { switchToScreen(Screen::Projects); });
  taskView->setOnExitRequest([this]() { handleExit(); });
  taskView->setOnCommentAdd([this](const std::string &commentText,
                                   int taskIndex, ProjectType project) {
    // Add comment to task
    if (taskController->addCommentToTask(
            taskIndex, project, commentText,
            authController->getCurrentUsername())) {
      // Successfully added comment, save tasks
      taskController->saveTasks();

      // Refresh the task view with the updated task data
      Task *updatedTask = taskController->getTask(taskIndex, project);
      if (updatedTask != nullptr) {
        auto taskCopy = std::make_unique<Task>(*updatedTask);
        taskView->setCurrentTask(std::move(taskCopy), taskIndex, project);
      }
    }
  });

  // Setup add task card view callbacks
  addTaskCardView->setOnTaskCardCreate(
      [this](const std::string &title, const std::string &assignedTo,
             int storyPoints, ProjectType project) {
        // Create and add new task card
        if (taskCardController->createTaskCard(title, assignedTo, storyPoints,
                                               project)) {
          // Successfully created task card, save and go back to projects
          taskCardController->saveTaskCards();
          switchToScreen(Screen::Projects);
        }
      });
  addTaskCardView->setOnBackRequest(
      [this]() { switchToScreen(Screen::Projects); });

  // Setup view task card view callbacks
  taskCardView->setOnBackRequest(
      [this]() { switchToScreen(Screen::Projects); });
  taskCardView->setOnExitRequest([this]() { handleExit(); });
  taskCardView->setOnCalculateTotalStoryPoints([this](ProjectType project) {
    return taskCardController->getTotalStoryPointsForProject(project);
  });

  // Setup add wiki page view callbacks
  addWikiPageView->setOnWikiPageCreate([this](const std::string &title,
                                              const std::string &content,
                                              ProjectType project) {
    // Create and add new wiki page
    if (wikiPageController->createWikiPage(title, content, project)) {
      // Successfully created wiki page, save and go back to projects with wiki
      // mode
      wikiPageController->saveWikiPages();
      currentViewMode = TaskViewMode::Wiki;
      switchToScreen(Screen::Projects);
    }
  });
  addWikiPageView->setOnBackRequest([this]() {
    currentViewMode = TaskViewMode::Wiki;
    switchToScreen(Screen::Projects);
  });

  // Setup view wiki page view callbacks
  wikiPageView->setOnBackRequest([this]() {
    currentViewMode = TaskViewMode::Wiki;
    switchToScreen(Screen::Projects);
  });
  wikiPageView->setOnExitRequest([this]() { handleExit(); });
}

/*
 * Helper method to handle the mock db functionality (reading/writing files)
 * Data is loaded through each controller
 */
void App::loadAppData() {
  taskController->loadTasks();
  taskCardController->loadTaskCards();
  wikiPageController->loadWikiPages();
  notificationController->loadNotifications();
}

/*
 * Handles initializing the GLUT graphics backend
 */
bool App::initializeGLUTBackend(int argc, char **argv) {
  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
  glutInitWindowSize(1280, 720);
  glutCreateWindow("Bloom - Project Management System");

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGLUT_Init();
  ImGui_ImplOpenGL2_Init();

  // Install GLUT handlers
  ImGui_ImplGLUT_InstallFuncs();

  // Setup GLUT display function after ImGui is initialized
  glutDisplayFunc(App::mainLoopStep);

  // Ensure keyboard repeat for text input
  glutIgnoreKeyRepeat(0);

  return true;
}

/*
 * Required cleanup functionality for GLUT backend
 */
void App::cleanupGraphics() {
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplGLUT_Shutdown();
  ImGui::DestroyContext();
}

/*
 * Begins the ImGUI/GLUT backend. Mostly required code from deraimgui github
 * Source:
 * https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl2/main.cpp
 */
void App::mainLoopStep() {
  // Error checking
  if (!instance)
    return;

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplGLUT_NewFrame();
  ImGui::NewFrame();

  // Render the current screen
  instance->renderCurrentScreen();

  // Rendering
  ImGui::Render();
  ImGuiIO &io = ImGui::GetIO();
  glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
  glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

  glutSwapBuffers();
  glutPostRedisplay();
}
