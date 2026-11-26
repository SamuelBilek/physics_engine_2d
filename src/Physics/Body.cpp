#include "Body.h"

Body::Body(const Shape& shape, float x, float y, float mass) : shape{shape.Clone()}, position{x, y}, mass{mass}
{
    if (mass != 0)
    {
        invMass = 1 / mass;
    }
    else
    {
        invMass = 0.0f;
    }
}

void Body::Integrate(float deltaTime)
{
    acceleration = sumForces * invMass;

    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    ClearForces();
}

void Body::AddForce(const Vec2& force)
{
    sumForces += force;
}

void Body::ClearForces()
{
    sumForces.x = 0;
    sumForces.y = 0;
}