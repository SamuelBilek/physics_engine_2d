#pragma once

#include "./Graphics.h"
#include "Physics/Particle.h"
#include <memory>

class Application
{
  private:
    bool m_running{false};
    std::unique_ptr<Particle> m_particle{nullptr};

  public:
    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
};