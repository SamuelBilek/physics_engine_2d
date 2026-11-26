#pragma once

#include "Particle.h"
#include "Vec2.h"

namespace Force
{
Vec2 GenerateDragForce(const Particle& particle, float k);

Vec2 GenerateFrictionForce(const Particle& particle, float k);

Vec2 GenerateGravitationalForce(const Particle& particleA, const Particle& particleB, float G, float minDistance,
                                float maxDistance);

Vec2 GenerateSpringForce(const Particle& particle, Vec2 anchor, float restLength, float k);
Vec2 GenerateSpringForce(const Particle& particleA, const Particle& particleB, float restLength, float k);
} // namespace Force