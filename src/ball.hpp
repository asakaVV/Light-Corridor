#pragma once

#include "drawable.hpp"

class Ball : public Drawable
{
public:
    Ball();

    void draw() override;

private:
    float _x;
    float _y;
    float _z;
};