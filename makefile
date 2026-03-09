# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

UNAME_S := $(shell uname -s)
# macOS
ifeq ($(UNAME_S), Darwin)
    LIBS = -framework OpenGL -framework GLUT
    CXXFLAGS += -DGL_SILENCE_DEPRECATION
# Linux
else
    LIBS = -lGL -lglut
endif

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = out
IMGUI_DIR = imgui

# Include paths
INCLUDES = -I$(INCDIR) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

# Required ImGui source files
IMGUI_SOURCES = $(IMGUI_DIR)/imgui.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp \
	$(IMGUI_DIR)/imgui_widgets.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_glut.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_opengl2.cpp

# Bloom source files
MODEL_SOURCES = $(SRCDIR)/models/User.cpp \
	$(SRCDIR)/models/Task.cpp \
    $(SRCDIR)/models/TaskCard.cpp \
	$(SRCDIR)/models/WikiPage.cpp \
	$(SRCDIR)/models/Notification.cpp \
	$(SRCDIR)/models/Comment.cpp

CONTROLLER_SOURCES = $(SRCDIR)/controllers/AuthController.cpp \
	$(SRCDIR)/controllers/TaskController.cpp \
	$(SRCDIR)/controllers/WikiController.cpp \
	$(SRCDIR)/controllers/TaskCardController.cpp \
	$(SRCDIR)/controllers/AnalyticsController.cpp \
	$(SRCDIR)/controllers/NotificationController.cpp \
	$(SRCDIR)/controllers/DataController.cpp \

VIEW_SOURCES = $(SRCDIR)/views/BaseView.cpp \
	$(SRCDIR)/views/LoginView.cpp \
	$(SRCDIR)/views/SetPasswordView.cpp \
	$(SRCDIR)/views/WelcomeView.cpp \
	$(SRCDIR)/views/ProjectsView.cpp \
	$(SRCDIR)/views/NotificationsView.cpp \
	$(SRCDIR)/views/AnalyticsView.cpp \
	$(SRCDIR)/views/AddTaskView.cpp \
	$(SRCDIR)/views/TaskView.cpp \
	$(SRCDIR)/views/AddTaskCardView.cpp \
	$(SRCDIR)/views/TaskCardView.cpp \
	$(SRCDIR)/views/AddWikiPageView.cpp \
	$(SRCDIR)/views/WikiPageView.cpp

APP_SOURCES = $(SRCDIR)/App.cpp

SOURCES = $(MODEL_SOURCES) $(CONTROLLER_SOURCES) $(VIEW_SOURCES) $(DAL_SOURCES) $(UTIL_SOURCES) $(APP_SOURCES)

# Object files
IMGUI_OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(IMGUI_SOURCES:.cpp=.o)))
APP_OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

# Main target
TARGET = $(OBJDIR)/bloom

all: directories $(TARGET)

# Create output directory
directories:
	@mkdir -p $(OBJDIR)

# Link the final executable
$(TARGET): $(IMGUI_OBJECTS) $(APP_OBJECTS) main.cpp
	@echo "Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ main.cpp $(IMGUI_OBJECTS) $(APP_OBJECTS) $(LIBS)
	@echo "Build complete: $(TARGET)"

# Compile ImGui objects
$(OBJDIR)/%.o: $(IMGUI_DIR)/%.cpp
	@echo "Compiling ImGui: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(IMGUI_DIR)/backends/%.cpp
	@echo "Compiling ImGui backend: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile application objects (with path resolution)
$(OBJDIR)/%.o: $(SRCDIR)/models/%.cpp
	@echo "Compiling Model: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/controllers/%.cpp
	@echo "Compiling Controller: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/views/%.cpp
	@echo "Compiling View: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/dal/%.cpp
	@echo "Compiling DAL: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(OBJDIR)

# Run the application
run: $(TARGET)
	@echo "Running Bloom..."
	./$(TARGET)
