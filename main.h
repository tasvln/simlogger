#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

// headers
#include "ext/window/Window.h"
#include "ext/texture/Texture.h"

using namespace std;
using namespace wdw;
using namespace txt;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 768;

TTF_Font *gFont = NULL;

void closeApp();