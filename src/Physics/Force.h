#pragma once

#include "Vec2.h"
#include <algorithm>

namespace Force
{
template <typename TBody>
Vec2 GenerateDragForce(const TBody& body, float k);

template <typename TBody>
Vec2 GenerateFrictionForce(const TBody& body, float k);

template <typename TBody>
Vec2 GenerateGravitationalForce(const TBody& bodyA, const TBody& bodyB, float G, float minDistance, float maxDistance);

template <typename TBody>
Vec2 GenerateSpringForce(const TBody& body, Vec2 anchor, float restLength, float k);

template <typename TBody>
Vec2 GenerateSpringForce(const TBody& bodyA, const TBody& bodyB, float restLength, float k);

//////////////////
// Implementation
//////////////////

template <typename TBody>
Vec2 GenerateDragForce(const TBody& body, float k)
{
    auto squareMag{body.velocity.MagnitudeSquared()};
    if (squareMag <= 0)
    {
        return Vec2{};
    }

    return -body.velocity.UnitVector() * k * squareMag;
}

template <typename TBody>
Vec2 GenerateFrictionForce(const TBody& body, float k)
{
    return -body.velocity.UnitVector() * k;
}

template <typename TBody>
Vec2 GenerateGravitationalForce(const TBody& bodyA, const TBody& bodyB, float G, float minDistance, float maxDistance)
{
    Vec2 d{bodyB.position - bodyA.position};

    // clamping for the purpose of displaying gravitation pull in small bodys
    float clampedDistanceSquared{d.MagnitudeSquared()};
    if (maxDistance >= minDistance && minDistance > 0.0f)
    {
        clampedDistanceSquared = std::clamp(clampedDistanceSquared, minDistance, maxDistance);
    }

    return G * (bodyA.mass * bodyB.mass / clampedDistanceSquared) * d.UnitVector();
}

template <typename TBody>
Vec2 GenerateSpringForce(const TBody& body, Vec2 anchor, float restLength, float k)
{
    Vec2 d{body.position - anchor};
    float displacement{d.Magnitude() - restLength};

    return -k * displacement * d.UnitVector();
}

template <typename TBody>
Vec2 GenerateSpringForce(const TBody& bodyA, const TBody& bodyB, float restLength, float k)
{
    return GenerateSpringForce(bodyA, bodyB.position, restLength, k);
}

} // namespace Force