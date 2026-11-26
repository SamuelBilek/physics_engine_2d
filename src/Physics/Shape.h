#pragma once

#include "Vec2.h"
#include <memory>
#include <vector>

enum class ShapeType
{
    CIRCLE,
    POLYGON,
    BOX
};

struct Shape
{

    virtual ShapeType GetType() const = 0;
    virtual std::unique_ptr<Shape> Clone() const = 0;
};

struct CircleShape : public Shape
{
    float radius{};

    CircleShape(float radius);
    ShapeType GetType() const override;
    std::unique_ptr<Shape> Clone() const override;
};

struct PolygonShape : public Shape
{
    std::vector<Vec2> vertices{};
    PolygonShape() = default;
    PolygonShape(const std::vector<Vec2>& vertices);
    ShapeType GetType() const override;
    std::unique_ptr<Shape> Clone() const override;
};

struct BoxShape : public PolygonShape
{
    float width{};
    float height{};

    BoxShape(float width, float height);
    ShapeType GetType() const override;
    std::unique_ptr<Shape> Clone() const override;
};