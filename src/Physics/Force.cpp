#include "Particle.h"
#include "Vec2.h"

#include <algorithm>

namespace Force
{
Vec2 GenerateDragForce(const Particle& particle, float k)
{
    auto squareMag{particle.velocity.MagnitudeSquared()};
    if (squareMag <= 0)
    {
        return Vec2{};
    }

    return -particle.velocity.UnitVector() * k * squareMag;
}

Vec2 GenerateFrictionForce(const Particle& particle, float k)
{
    return -particle.velocity.UnitVector() * k;
}

Vec2 GenerateGravitationalForce(const Particle& particleA, const Particle& particleB, float G, float minDistance = 0,
                                float maxDistance = 0)
{
    Vec2 d{particleB.position - particleA.position};

    // clamping for the purpose of displaying gravitation pull in small particles
    float clampedDistanceSquared{d.MagnitudeSquared()};
    if (maxDistance >= minDistance && minDistance > 0.0f)
    {
        clampedDistanceSquared = std::clamp(clampedDistanceSquared, minDistance, maxDistance);
    }

    return G * (particleA.mass * particleB.mass / clampedDistanceSquared) * d.UnitVector();
}

Vec2 GenerateSpringForce(const Particle& particle, Vec2 anchor, float restLength, float k)
{
    Vec2 d{particle.position - anchor};
    float displacement{d.Magnitude() - restLength};

    return -k * displacement * d.UnitVector();
}

Vec2 GenerateSpringForce(const Particle& particleA, const Particle& particleB, float restLength, float k)
{
    return GenerateSpringForce(particleA, particleB.position, restLength, k);
}
} // namespace Force