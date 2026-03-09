#ifndef WIKIPAGEVIEW_H
#define WIKIPAGEVIEW_H

#include "BaseView.h"
#include "../models/WikiPage.h"
#include <functional>
#include <memory>

class WikiPageView : public BaseView {
private:
    std::unique_ptr<WikiPage> currentWikiPage;
    int currentWikiPageIndex;
    ProjectType currentProject;
    
    // Callback functions for user actions
    std::function<void()> onBackRequest;
    std::function<void()> onExitRequest;
    
public:
    WikiPageView();
    ~WikiPageView() = default;
    
    // Override from BaseView
    void render() override;
    
    // Setters for callbacks
    void setOnBackRequest(std::function<void()> callback);
    void setOnExitRequest(std::function<void()> callback);
    
    // Set data
    void setCurrentWikiPage(std::unique_ptr<WikiPage> wikiPage, int index, ProjectType project);
    
private:
    void renderWikiPageMenu();
    void renderWikiPageContent();
    std::string projectTypeToString(ProjectType project) const;
};

#endif // WIKIPAGEVIEW_H
