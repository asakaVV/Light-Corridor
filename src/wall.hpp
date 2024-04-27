#pragma once

#include "drawable.hpp"
#include <vector>

class Wall : public Drawable
{
public:
    Wall(std::vector<float> center, std::vector<float> size, float rotation, std::vector<float> color);

    void draw() override;

private:
    float _center[3];
    float _size[3];
    float _rotation;
    float _color[3];
};