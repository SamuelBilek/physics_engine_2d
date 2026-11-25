#pragma once

#include "./Graphics.h"

class Application
{
  private:
    bool m_running = false;

  public:
    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
};