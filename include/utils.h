#ifndef UTILS_H
#define UTILS_H

#include "../imgui/backends/imgui_impl_glut.h"
#include "../imgui/backends/imgui_impl_opengl2.h"
#include "../imgui/imgui.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <chrono>
#include <map>
#include <string>
#include <vector>

// Forward declarations for model types
class Task;
class TaskCard;
class WikiPage;
class Notification;
class Comment;

// Enums from original implementation - moved from models to avoid duplication
enum class TaskViewMode { Tasks, Sprint, Wiki };

#endif // UTILS_H
