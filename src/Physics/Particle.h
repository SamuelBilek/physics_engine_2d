#pragma once

#include "Vec2.h"

struct Particle
{
    Vec2 position{};
    Vec2 velocity{};
    Vec2 acceleration{};

    int radius{1};
    float mass{1.0f};

    Particle(float x, float y, float mass);
    ~Particle();

    void Integrate(float deltaTime);
};