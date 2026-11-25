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
    auto smallBall{std::make_unique<Particle>(50, 100, 1.0)};
    smallBall->radius = 4;

    m_particles.push_back(std::move(smallBall));

    // auto bigBall{std::make_unique<Particle>(200, 100, 3.0)};
    // bigBall->radius = 12;

    // m_particles.push_back(std::move(bigBall));

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
            if (event.key.keysym.sym == SDLK_UP)
                m_pushForce.y = -50 * Constants::PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_RIGHT)
                m_pushForce.x = 50 * Constants::PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_DOWN)
                m_pushForce.y = 50 * Constants::PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_LEFT)
                m_pushForce.x = -50 * Constants::PIXELS_PER_METER;
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

    Vec2 wind{1.0 * Constants::PIXELS_PER_METER, 0.0};
    Vec2 gravity(0.0, 9.8 * Constants::PIXELS_PER_METER);

    for (auto& particle : m_particles)
    {
        particle->AddForce(m_pushForce);
        particle->AddForce(wind);
        particle->AddForce(gravity * particle->mass);

        particle->Integrate(deltaTime);

        if (particle->position.x + particle->radius > Graphics::Width())
        {
            particle->position.x = Graphics::Width() - particle->radius;
            particle->velocity.x *= -0.9f;
        }
        if (particle->position.x - particle->radius < 0)
        {
            particle->position.x = particle->radius;
            particle->velocity.x *= -0.9f;
        }

        if (particle->position.y + particle->radius > Graphics::Height())
        {
            particle->position.y = Graphics::Height() - particle->radius;
            particle->velocity.y *= -0.9f;
        }
        if (particle->position.y - particle->radius < 0)
        {
            particle->position.y = particle->radius;
            particle->velocity.y *= -0.9f;
        }
    }
    m_pushForce.x = 0;
    m_pushForce.y = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render()
{
    Graphics::ClearScreen(0xFF056263);
    for (const auto& particle : m_particles)
    {
        Graphics::DrawFillCircle(particle->position.x, particle->position.y, particle->radius, 0xFFFFFFFF);
    }
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