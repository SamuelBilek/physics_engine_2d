#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass) : position{x, y}, mass{mass}
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

Particle::Particle(float x, float y, int radius, float mass) : Particle(x, y, mass)
{
    this->radius = radius;
}

void Particle::Integrate(float deltaTime)
{
    acceleration = sumForces * invMass;

    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    ClearForces();
}

void Particle::AddForce(const Vec2& force)
{
    sumForces += force;
}

void Particle::ClearForces()
{
    sumForces.x = 0;
    sumForces.y = 0;
}