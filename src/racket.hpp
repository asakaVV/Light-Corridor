#pragma once

#include "drawable.hpp"
#include "ball.hpp"

class Racket : public Drawable
{
public:
    Racket();

    void move(float x, float y, float z);

    void draw() const override;

    bool collide(Ball &ball);

    void get_position(float &x, float &y, float &z) const;

    void get_scale(float &x, float &y) const;

private:
    float _x;
    float _y;
    float _z;
    float _scale_y = 4.0;
    float _scale_x = 4.0;
};