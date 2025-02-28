// Simple Logger v1.0.0
// This Project is dependent on IMGUI and can be used with
// SDL & GLFW. This is just a simple Logger Class

#ifndef SIMLOGGER_H
#define SIMLOGGER_H

#include <iostream>
#include <vector>
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

// DEBUG_TYPE:  enum for debug types
enum DEBUG_TYPE
{
  INFO,
  WARNING,
  OPTIONAL,
  NOT_SUPPORTED,
  SUPPORTED,
  ERROR
};

namespace SimLog
{
  // Simple Logger Class
  class SimLogger
  {
  private:
    // boolean var to show debug gui
    bool visible;
    // list: to store all log types and messages
    std::vector<std::string> logs;

  public:
    // Constructor
    SimLogger()
    {
      // On Screen log is disabled by default
      visible = false;
    }

    // toggleLog: recursive toggle function, to be called with the event handler
    // (keydown or joystick behaviour)
    void toggleLog()
    {
      visible = !visible;
    }

    // addLog: add the the list of messages/log to the list that would showed/displayed
    // on screen
    void addLog(const std::string &message)
    {
      logs.push_back(message);
    }

    // render: render the logs on screen only when it has been toggled, to be called in
    // the game loop
    void render()
    {
      if (!visible)
        return;

      // Loop through vector list
      for (const auto &log : logs)
      {
        // Print logs using ImGUI
        ImGui::Begin("Simple Logger Console");

        ImGui::TextUnformatted(log.c_str());

        ImGui::End();
      }
    }

    // log: print out console log messages with their assign debug types
    void log(const std::string &message, DEBUG_TYPE type)
    {
      std::string typeStr;

      switch (type)
      {
      case INFO:
        typeStr = "[INFO]: ";
        break;
      case WARNING:
        typeStr = "[WARNING]: ";
        break;
      case OPTIONAL:
        typeStr = "[OPTIONAL]: ";
        break;
      case NOT_SUPPORTED:
        typeStr = "[NOT SUPPORTED]: ";
        break;
      case SUPPORTED:
        typeStr = "[SUPPORTED]: ";
        break;
      case ERROR:
        typeStr = "[ERROR]: ";
        break;
      }

      std::string fullMessage = typeStr + message;
      std::cout << fullMessage << std::endl;
    }
  };
}

#endif