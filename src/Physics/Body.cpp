#include "Body.h"

Body::Body(const Shape& shape, float x, float y, float mass) : shape{shape.Clone()}, position{x, y}, mass{mass}
{
    invMass = (mass != 0.0f) ? (1 / mass) : 0.0f;
    momentOfInertia = shape.GetMomentOfInertia() * mass;
    invMomentOfInertia = (momentOfInertia != 0.0f) ? (1 / momentOfInertia) : 0.0f;
}

void Body::AddForce(const Vec2& force)
{
    sumForces += force;
}

void Body::AddTorque(float torque)
{
    sumTorque += torque;
}

void Body::ClearForces()
{
    sumForces.x = 0;
    sumForces.y = 0;
}

void Body::ClearTorque()
{
    sumTorque = 0;
}

void Body::IntegrateLinear(float deltaTime)
{
    acceleration = sumForces * invMass;

    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    ClearForces();
}

void Body::IntegrateAngular(float deltaTime)
{
    angularAcceleration = sumTorque * invMomentOfInertia;

    angularVelocity += angularAcceleration * deltaTime;
    rotation += angularVelocity * deltaTime;

    ClearTorque();
}