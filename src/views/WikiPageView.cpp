#include "../../include/views/WikiPageView.h"

WikiPageView::WikiPageView() : BaseView() {
  currentWikiPage = nullptr;
  currentWikiPageIndex = -1;
  currentProject = ProjectType::NONE;
}

/*
 * Renders single wiki page screen
 */
void WikiPageView::render() {
  ImGuiIO &io = getIO();

  // Left side menu
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(200, io.DisplaySize.y), ImGuiCond_Always);

  if (ImGui::Begin("Wiki Page View Menu", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoScrollbar)) {
    renderWikiPageMenu();
  }

  ImGui::End();

  // Right side content
  ImGui::SetNextWindowPos(ImVec2(200, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 200, io.DisplaySize.y),
                           ImGuiCond_Always);

  if (ImGui::Begin("Wiki Page Details", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse |
                       ImGuiWindowFlags_NoTitleBar)) {
    renderWikiPageContent();
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void WikiPageView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void WikiPageView::setOnExitRequest(std::function<void()> callback) {
  onExitRequest = callback;
}

/*
 * Helper method to set current wiki page
 */
void WikiPageView::setCurrentWikiPage(std::unique_ptr<WikiPage> wikiPage,
                                      int index, ProjectType project) {
  currentWikiPage = std::move(wikiPage);
  currentWikiPageIndex = index;
  currentProject = project;
}

/*
 * Declares contents of left side menu for rendering
 */
void WikiPageView::renderWikiPageMenu() {
  ImGui::Text("MENU");
  ImGui::Separator();

  // Bottom buttons
  ImGuiIO &io = getIO();
  ImGui::SetCursorPosY(io.DisplaySize.y - 90);
  ImGui::Separator();

  if (ImGui::Button("<= Back to Wiki", ImVec2(180, 30)) && onBackRequest) {
    currentWikiPage = nullptr;
    currentWikiPageIndex = -1;
    onBackRequest();
  }

  if (ImGui::Button("Exit", ImVec2(180, 30)) && onExitRequest) {
    onExitRequest();
  }
}

/*
 * Declares contents of right main content window for rendering
 */
void WikiPageView::renderWikiPageContent() {
  // Basic error checking before displaying wiki page
  if (currentWikiPage != nullptr) {
    // Title
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Text("Wiki Page: %s", currentWikiPage->getTitle().c_str());
    ImGui::PopFont();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Project
    ImGui::Text("Project:");
    ImGui::SameLine(150);
    std::string projectName = projectTypeToString(currentProject);
    ImGui::Text("%s", projectName.c_str());

    ImGui::Spacing();
    ImGui::Spacing();

    // Page content label
    ImGui::Text("Content:");
    ImGui::Separator();
    ImGui::Spacing();

    // Scrollable text box for content
    ImGui::BeginChild("WikiContent", ImVec2(0, 400), true,
                      ImGuiWindowFlags_AlwaysVerticalScrollbar);
    ImGui::TextWrapped("%s", currentWikiPage->getContent().c_str());
    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Action buttons
    if (ImGui::Button("Edit Page", ImVec2(100, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete Page", ImVec2(100, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::SameLine();

    if (ImGui::Button("Print Page", ImVec2(100, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::Spacing();

    // Additional wiki management buttons
    if (ImGui::Button("Create Related Page", ImVec2(140, 30))) {
      // Stub functionatliy for now...
    }

    ImGui::SameLine();

    if (ImGui::Button("Page History", ImVec2(100, 30))) {
      // Stub functionatliy for now...
    }

  } else {
    // Display basic error state
    ImGui::Text("Error: No wiki page selected");
  }
}

/*
 * Helper method to convert enum type to string representation
 */
std::string WikiPageView::projectTypeToString(ProjectType project) const {
  switch (project) {
  case ProjectType::DEPLOY:
    return "DEPLOY";
  case ProjectType::FLOW:
    return "FLOW";
  case ProjectType::BLOOM:
    return "BLOOM";
  default:
    return "NONE";
  }
}
