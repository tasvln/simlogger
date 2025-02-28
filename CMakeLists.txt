cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

project(SIMLOGGER VERSION 1.0.0)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Variables storing SDL framework locations
set(SDL2
  /Library/Frameworks/SDL2.framework)
set(SDL2_image
  /Library/Frameworks/SDL2_image.framework)
set(SDL2_ttf
  /Library/Frameworks/SDL2_ttf.framework)

set(IMGUI_SOURCES
  lib/include/imgui/imgui.cpp
  lib/include/imgui/imgui_draw.cpp
  lib/include/imgui/imgui_widgets.cpp
  lib/include/imgui/imgui_tables.cpp
  lib/include/imgui/imgui_impl_sdl2.cpp
  lib/include/imgui/imgui_impl_opengl3.cpp
)

include_directories(
  ${CMAKE_SOURCE_DIR}/lib/include
)

add_executable(SIMLOGGER main.cpp lib/glad.c ext/texture/Texture.cpp ${IMGUI_SOURCES})

target_link_libraries(
  SIMLOGGER PRIVATE
  ${SDL2}/Versions/A/SDL2
  ${SDL2_image}/Versions/A/SDL2_image
  ${SDL2_ttf}/Versions/A/SDL2_ttf
  glfw
  OpenGL::GL
)

target_include_directories(
  SIMLOGGER PRIVATE
  ${SDL2}/Versions/A/Headers
  ${SDL2_image}/Versions/A/Headers
  ${SDL2_ttf}/Versions/A/Headers
)