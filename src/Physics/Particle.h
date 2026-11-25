#pragma once

#include "Vec2.h"

struct Particle
{
    Vec2 position{};
    Vec2 velocity{};
    Vec2 acceleration{};

    int radius{1};

    float mass{1.0f};
    float invMass{1.0f};

    Vec2 sumForces{};

    Particle(float x, float y, float mass);
    ~Particle();

    void Integrate(float deltaTime);

    void AddForce(const Vec2& force);

    void ClearForces();
};