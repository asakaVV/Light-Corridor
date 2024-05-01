#pragma once

#include "drawable.hpp"
#include <vector>
#include "ball.hpp"

class Wall : public Drawable
{
public:
    enum class WallType
    {
        TOP,
        LEFT,
        RIGHT,
        BOTTOM
    };

    Wall(std::vector<float> center, std::vector<float> size, float rotation, std::vector<float> color, WallType type);

    void draw() const override;

    void collide(Ball &ball);

private:
    float _center[3];
    float _size[3];
    float _rotation;
    float _color[3];
    WallType _type;
};