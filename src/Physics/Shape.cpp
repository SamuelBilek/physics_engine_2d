#include "Shape.h"

CircleShape::CircleShape(float radius) : radius{radius}
{
}

ShapeType CircleShape::GetType() const
{
    return ShapeType::CIRCLE;
}

std::unique_ptr<Shape> CircleShape::Clone() const
{
    return std::make_unique<CircleShape>(radius);
}

float CircleShape::GetMomentOfInertia() const
{
    return 0.5f * (radius * radius);
}

PolygonShape::PolygonShape(const std::vector<Vec2>& vertices) : vertices{vertices}
{
}

ShapeType PolygonShape::GetType() const
{
    return ShapeType::POLYGON;
}

std::unique_ptr<Shape> PolygonShape::Clone() const
{
    return std::make_unique<PolygonShape>(vertices);
}

float PolygonShape::GetMomentOfInertia() const
{
    // TODO
    return 0.0f;
}

BoxShape::BoxShape(float width, float height) : width{width}, height{height}
{
}

ShapeType BoxShape::GetType() const
{
    return ShapeType::BOX;
}

std::unique_ptr<Shape> BoxShape::Clone() const
{
    return std::make_unique<BoxShape>(width, height);
}

float BoxShape::GetMomentOfInertia() const
{
    return (1 / 12.0f) * (width * width + height * height);
}