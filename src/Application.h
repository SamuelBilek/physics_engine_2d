#pragma once

#include "./Graphics.h"
#include "Physics/Body.h"
#include <memory>
#include <vector>

class Application
{
  private:
    bool m_running{false};
    std::vector<std::unique_ptr<Body>> m_bodies{};
    Vec2 m_pushForce{};

    Vec2 m_mouseCursor = Vec2{};
    bool m_leftMouseButtonDown = false;

    Vec2 m_anchor{};
    float m_springConstant{100.0f};
    float m_restLength{400};

  public:
    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
};