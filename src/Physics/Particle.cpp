#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass) : position{x, y}, mass{mass}
{
    std::cout << "Particle constructor called" << std::endl;
}

Particle::~Particle()
{
    std::cout << "Particle destructor called" << std::endl;
}

void Particle::Integrate(float deltaTime)
{
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}