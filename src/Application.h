#pragma once

#include "./Graphics.h"
#include "Physics/Particle.h"
#include <memory>
#include <vector>

class Application
{
  private:
    bool m_running{false};
    std::vector<std::unique_ptr<Particle>> m_particles{};
    Vec2 m_pushForce{};

  public:
    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
};