#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

// headers
// #include "ext/window/Window.h"
#include "ext/texture/Texture.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

#include "ext/simlogger/SimLogger.h"

using namespace std;
// using namespace wdw;
using namespace txt;
using namespace SimLog;
using namespace ImGui;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 768;

TTF_Font *gFont = NULL;

SimLogger logger;

void closeApp();