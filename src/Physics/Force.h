#pragma once

#include "Particle.h"
#include "Vec2.h"

namespace Force
{
Vec2 GenerateDragForce(const Particle& particle, float k);

Vec2 GenerateFrictionForce(const Particle& particle, float k);
} // namespace Force