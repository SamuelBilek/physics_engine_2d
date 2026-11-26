#pragma once

#include "Shape.h"
#include "Vec2.h"
#include <memory>

struct Body
{
    std::unique_ptr<Shape> shape{nullptr};

    Vec2 position{};
    Vec2 velocity{};
    Vec2 acceleration{};

    float mass{1.0f};
    float invMass{1.0f};

    Vec2 sumForces{};
    Body(const Shape& shape, float x, float y, float mass);

    void Integrate(float deltaTime);

    void AddForce(const Vec2& force);

    void ClearForces();
};