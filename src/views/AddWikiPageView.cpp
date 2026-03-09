#include "../../include/views/AddWikiPageView.h"

AddWikiPageView::AddWikiPageView() : BaseView() {
  currentProject = ProjectType::NONE;
  memset(newWikiPageTitle, 0, sizeof(newWikiPageTitle));
  memset(newWikiPageText, 0, sizeof(newWikiPageText));
  showTitleError = false;
  errorMessage = "";
}

/*
 * Renders add wiki page screen
 */
void AddWikiPageView::render() {
  ImGuiIO &io = getIO();

  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);

  if (ImGui::Begin("Add Wiki Page", nullptr,
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoCollapse)) {
    // clear the form and direct user back to projects screen
    if (ImGui::Button("<= Back", ImVec2(100, 30)) && onBackRequest) {
      clearForm();
      onBackRequest();
    }

    ImGui::Separator();
    ImGui::Spacing();

    // page title
    ImGui::Text("Wiki Page Title:");
    if (showTitleError) {
      ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.2f, 0.2f, 0.3f));
      ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,
                            ImVec4(0.8f, 0.2f, 0.2f, 0.4f));
      ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                            ImVec4(0.8f, 0.2f, 0.2f, 0.5f));
    }

    ImGui::InputText("##title", newWikiPageTitle, sizeof(newWikiPageTitle),
                     ImGuiInputTextFlags_AllowTabInput);

    if (showTitleError) {
      ImGui::PopStyleColor(3);
    }

    ImGui::Spacing();

    // page text
    ImGui::Text("Wiki Page Text:");
    ImGui::InputTextMultiline("##pagetext", newWikiPageText,
                              sizeof(newWikiPageText), ImVec2(400, 200),
                              ImGuiInputTextFlags_AllowTabInput);
    ImGui::Spacing();

    // Display error message
    if (showTitleError && !errorMessage.empty()) {
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
      ImGui::Text("%s", errorMessage.c_str());
      ImGui::PopStyleColor();
      ImGui::Spacing();
    }

    // create wiki page
    if (ImGui::Button("Create", ImVec2(100, 30))) {
      // Basic input validation
      if (strlen(newWikiPageTitle) == 0) {
        showTitleError = true;
        errorMessage = "Page title cannot be empty";
      } else {
        showTitleError = false;
        errorMessage = "";
        if (onWikiPageCreate) {
          // Create the wiki page
          onWikiPageCreate(std::string(newWikiPageTitle),
                           std::string(newWikiPageText), currentProject);
          clearForm();
        }
      }
    }
  }

  ImGui::End();
}

/*
 * Event handlers
 */
void AddWikiPageView::setOnWikiPageCreate(
    std::function<void(const std::string &, const std::string &, ProjectType)>
        callback) {
  onWikiPageCreate = callback;
}

void AddWikiPageView::setOnBackRequest(std::function<void()> callback) {
  onBackRequest = callback;
}

void AddWikiPageView::setCurrentProject(ProjectType project) {
  currentProject = project;
}

/*
 * Helper method to clear form
 */
void AddWikiPageView::clearForm() {
  memset(newWikiPageTitle, 0, sizeof(newWikiPageTitle));
  memset(newWikiPageText, 0, sizeof(newWikiPageText));
  showTitleError = false;
  errorMessage = "";
}

/*
 * Helper method to convert enum type to string representation
 */
std::string AddWikiPageView::projectTypeToString(ProjectType project) const {
  switch (project) {
  case ProjectType::DEPLOY:
    return "Deploy";
  case ProjectType::FLOW:
    return "Flow";
  case ProjectType::BLOOM:
    return "Bloom";
  default:
    return "None";
  }
}
