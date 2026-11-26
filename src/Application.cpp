#include "Application.h"
#include "Physics/Constants.h"
#include "Physics/Force.h"

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

    auto smallBall{std::make_unique<Particle>(50, 100, 4, 1.0)};
    m_particles.push_back(std::move(smallBall));

    auto bigBall{std::make_unique<Particle>(200, 100, 12, 3.0)};
    m_particles.push_back(std::move(bigBall));

    m_liquid.x = 0;
    m_liquid.y = Graphics::Height() / 2;
    m_liquid.w = Graphics::Width();
    m_liquid.h = Graphics::Height() / 2;
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input()
{
    SDL_Event event;
    int mouseX{};
    int mouseY{};
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&mouseX, &mouseY);
            m_particles.push_back(std::move(std::make_unique<Particle>(mouseX, mouseY, 4, 1.0)));
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

    Vec2 gravity(0.0, 9.8 * Constants::PIXELS_PER_METER);

    for (auto& particle : m_particles)
    {
        particle->AddForce(m_pushForce);
        particle->AddForce(gravity * particle->mass);

        if (particle->position.y >= m_liquid.y)
        {
            Vec2 drag{Force::GenerateDragForce(*particle, 0.03)};
            particle->AddForce(drag);
        }

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
    Graphics::DrawFillRect(
        m_liquid.x + m_liquid.w / 2, m_liquid.y + m_liquid.h / 2, m_liquid.w, m_liquid.h, 0xFF6E3713);

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