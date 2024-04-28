#pragma once

#include "drawable.hpp"

class Ball : public Drawable
{
public:
    Ball();

    void draw() override;

    void set_grip(bool grip);

    bool get_grip() const;

    void move(float x, float y, float z);

    void set_speed(float x, float y, float z);

    void get_speed(float &x, float &y, float &z) const;

    void update();

    void move_with_delta(float delta);

    void get_position(float &x, float &y, float &z) const;

private:
    float _x;
    float _y;
    float _z;
    bool _grip;
    float _x_speed = -0.3;
    float _y_speed = 0.0;
    float _z_speed = 0.0;
};