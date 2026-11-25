#include "Application.h"
#include "Physics/Constants.h"

bool Application::IsRunning()
{
    return m_running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup()
{
    m_running = Graphics::OpenWindow();
    m_particle = std::make_unique<Particle>(50, 100, 1.0);
    m_particle->radius = 4;

    // TODO: setup objects in the scene
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                m_running = false;
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update()
{
    static Uint32 timePrevFrame{};
    Uint32 ticks{SDL_GetTicks()};
    int timeToWait{Constants::MILISECS_PER_FRAME - static_cast<int>((ticks - timePrevFrame))};
    if (timeToWait > 0)
    {
        SDL_Delay(timeToWait);
    }

    float deltaTime{(ticks - timePrevFrame) / 1000.0f};
    if (deltaTime > Constants::MILISECS_PER_FRAME / 1000.0f)
    {
        deltaTime = Constants::MILISECS_PER_FRAME / 1000.0f;
    }

    timePrevFrame = ticks;

    m_particle->acceleration.x = 2.0f * Constants::PIXELS_PER_METER;
    m_particle->acceleration.y = 9.8f * Constants::PIXELS_PER_METER;

    m_particle->velocity += m_particle->acceleration * deltaTime;
    m_particle->position += m_particle->velocity * deltaTime;

    if (m_particle->position.x + m_particle->radius > Graphics::Width())
    {
        m_particle->position.x = Graphics::Width() - m_particle->radius;
        m_particle->velocity.x *= -0.9f;
    }
    if (m_particle->position.x - m_particle->radius < 0)
    {
        m_particle->position.x = m_particle->radius;
        m_particle->velocity.x *= -0.9f;
    }

    if (m_particle->position.y + m_particle->radius > Graphics::Height())
    {
        m_particle->position.y = Graphics::Height() - m_particle->radius;
        m_particle->velocity.y *= -0.9f;
    }
    if (m_particle->position.y - m_particle->radius < 0)
    {
        m_particle->position.y = m_particle->radius;
        m_particle->velocity.y *= -0.9f;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render()
{
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(m_particle->position.x, m_particle->position.y, m_particle->radius, 0xFFFFFFFF);
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy()
{
    // TODO: destroy all objects in the scene

    Graphics::CloseWindow();
}