#include "Particle.h"
#include "Vec2.h"

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
} // namespace Force