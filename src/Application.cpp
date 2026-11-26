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

    auto body{std::make_unique<Body>(CircleShape{50}, Graphics::Width() / 2.0, Graphics::Height() / 2.0, 1.0)};
    m_bodies.push_back(std::move(body));
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
                Vec2 impulseDirection = (m_bodies[0]->position - m_mouseCursor).UnitVector();
                float impulseMagnitude = (m_bodies[0]->position - m_mouseCursor).Magnitude() * 5.0;
                m_bodies[0]->velocity = impulseDirection * impulseMagnitude;
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

    for (auto& body : m_bodies)
    {
        body->AddForce(m_pushForce);

        Vec2 weightForce{0.0f, body->mass * 9.8f * static_cast<float>(Constants::PIXELS_PER_METER)};
        body->AddForce(weightForce);
    }

    for (auto& body : m_bodies)
    {
        if (body->shape->GetType() == ShapeType::CIRCLE)
        {
            CircleShape& circleShape{dynamic_cast<CircleShape&>(*body->shape)};
            if (body->position.x + circleShape.radius > Graphics::Width())
            {
                body->position.x = Graphics::Width() - circleShape.radius;
                body->velocity.x *= -0.9f;
            }
            if (body->position.x - circleShape.radius < 0)
            {
                body->position.x = circleShape.radius;
                body->velocity.x *= -0.9f;
            }

            if (body->position.y + circleShape.radius > Graphics::Height())
            {
                body->position.y = Graphics::Height() - circleShape.radius;
                body->velocity.y *= -0.9f;
            }
            if (body->position.y - circleShape.radius < 0)
            {
                body->position.y = circleShape.radius;
                body->velocity.y *= -0.9f;
            }
        }
        body->Integrate(deltaTime);
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

    static float angle{0.0f};

    for (const auto& body : m_bodies)
    {
        if (body->shape->GetType() == ShapeType::CIRCLE)
        {
            CircleShape& circleShape{dynamic_cast<CircleShape&>(*body->shape)};
            Graphics::DrawCircle(body->position.x, body->position.y, circleShape.radius, angle, 0xFFFFFFFF);
        }
    }

    angle += 0.01f;

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