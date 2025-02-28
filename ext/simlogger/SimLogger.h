#ifndef SIMLOGGER_H
#define SIMLOGGER_H

#include <iostream>
#include <vector>
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

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
  class SimLogger
  {
  private:
    bool visible;
    std::vector<std::string> logs;

  public:
    // On Window/Screen Logs
    SimLogger()
    {
      visible = false;
    }

    void toggleLog()
    {
      visible = !visible;
    }

    void addLog(const std::string &message)
    {
      logs.push_back(message);
    }

    void render()
    {
      if (!visible)
        return;
      for (const auto &log : logs)
      {
        ImGui::Begin("Debug Console");

        ImGui::TextUnformatted(log.c_str());

        ImGui::End();
      }
    }

    // console logging
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
      addLog(fullMessage);
    }
  };
}

#endif