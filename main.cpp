#include "main.h"

bool loadMedia()
{
  bool loading = true;

  gFont = TTF_OpenFont("lib/fonts/inter.ttf", 28);

  if (gFont == NULL)
  {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    loading = false;
  }

  return loading;
}

void closeApp()
{
  if (gFont != NULL)
  {
    TTF_CloseFont(gFont);
    gFont = NULL;
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  TTF_Quit();
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }
  else
  {

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
      printf("Warning: Linear texture filtering not enabled!");
    }

    if (TTF_Init() == -1)
    {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    SDL_Window *window = SDL_CreateWindow("SIMLOGGER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window)
    {
      printf("Failed to initialize Window!\n");
    }
    else
    {
      SDL_GLContext glContext = SDL_GL_CreateContext(window);
      SDL_GL_MakeCurrent(window, glContext);

      if (!glContext)
      {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return -1;
      }

      if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
      {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
      }

      ImGui::CreateContext();
      ImGui_ImplSDL2_InitForOpenGL(window, glContext);
      ImGui_ImplOpenGL3_Init();

      logger.log("Initializing...", DEBUG_TYPE::INFO);
      logger.addLog("ImGUI Pop UP");

      if (!loadMedia())
      {
        printf("Failed to load Images/Textures!\n");
      }
      else
      {
        bool isRunning = true;
        SDL_Event evt;

        while (isRunning)
        {
          while (SDL_PollEvent(&evt) != 0)
          {
            if (evt.type == SDL_QUIT)
            {
              isRunning = false;
            }
            if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_LEFT)
              logger.toggleLog();
          }

          glClear(GL_COLOR_BUFFER_BIT);

          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplSDL2_NewFrame();
          ImGui::NewFrame();

          logger.render();

          ImGui::Render();
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
          SDL_GL_SwapWindow(window);
        }
      }

      SDL_GL_DeleteContext(glContext);
    }
  }

  return 0;
}