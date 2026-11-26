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

    m_anchor.x = Graphics::Width() / 2.0;
    m_anchor.y = 30.0f;

    auto bob{std::make_unique<Particle>(Graphics::Width() / 2.0, Graphics::Height() / 2.0, 10, 2.0)};
    m_particles.push_back(std::move(bob));
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
        case SDL_MOUSEMOTION:
            m_mouseCursor.x = event.motion.x;
            m_mouseCursor.y = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (!m_leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
            {
                m_leftMouseButtonDown = true;
                int x, y;
                SDL_GetMouseState(&x, &y);
                m_mouseCursor.x = x;
                m_mouseCursor.y = y;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (m_leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
            {
                m_leftMouseButtonDown = false;
                Vec2 impulseDirection = (m_particles[0]->position - m_mouseCursor).UnitVector();
                float impulseMagnitude = (m_particles[0]->position - m_mouseCursor).Magnitude() * 5.0;
                m_particles[0]->velocity = impulseDirection * impulseMagnitude;
            }
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

    for (auto& particle : m_particles)
    {
        particle->AddForce(m_pushForce);

        Vec2 drag{Force::GenerateDragForce(*particle, 0.001)};
        particle->AddForce(drag);

        Vec2 weightForce{0.0f, particle->mass * 9.8f * static_cast<float>(Constants::PIXELS_PER_METER)};
        particle->AddForce(weightForce);
    }

    Vec2 springForce{Force::GenerateSpringForce(*m_particles[0], m_anchor, m_restLength, m_springConstant)};
    m_particles[0]->AddForce(springForce);

    for (auto& particle : m_particles)
    {
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
    Graphics::ClearScreen(0xFF0F0721);

    if (m_leftMouseButtonDown)
    {
        Graphics::DrawLine(
            m_particles[0]->position.x, m_particles[0]->position.y, m_mouseCursor.x, m_mouseCursor.y, 0xFF0000FF);
    }

    // Draw spring
    Graphics::DrawLine(m_anchor.x, m_anchor.y, m_particles[0]->position.x, m_particles[0]->position.y, 0xFF313131);
    // Draw anchor
    Graphics::DrawFillCircle(m_anchor.x, m_anchor.y, 5, 0xFF001155);
    // Draw bob
    Graphics::DrawFillCircle(
        m_particles[0]->position.x, m_particles[0]->position.y, m_particles[0]->radius, 0xFFFFFFFF);

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