#pragma once

#include "drawable.hpp"
#include "ball.hpp"

class Racket : public Drawable
{
public:
    Racket();

    void move(float x, float y, float z);

    void draw() const override;

    void collide(Ball &ball);

private:
    float _x;
    float _y;
    float _z;
    float _scale_y = 4.0;
    float _scale_x = 4.0;
};