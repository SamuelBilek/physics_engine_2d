#pragma once

#include "Shape.h"
#include "Vec2.h"
#include <memory>

struct Body
{
    std::unique_ptr<Shape> shape{nullptr};

    // Linear motion
    Vec2 position{};
    Vec2 velocity{};
    Vec2 acceleration{};

    // Angular motion
    float rotation{};
    float angularVelocity{};
    float angularAcceleration{};

    // Forces and torque
    Vec2 sumForces{};
    float sumTorque{};

    // Mass and Moment of Inertia
    float mass{1.0f};
    float invMass{1.0f};
    float momentOfInertia{};
    float invMomentOfInertia{};

    Body(const Shape& shape, float x, float y, float mass);

    void AddForce(const Vec2& force);
    void AddTorque(float torque);

    void ClearForces();
    void ClearTorque();

    void IntegrateLinear(float deltaTime);
    void IntegrateAngular(float deltaTime);
};