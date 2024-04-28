#pragma once

#include "drawable.hpp"

class Ball : public Drawable
{
public:
    Ball();

    void draw() override;

    void change_grip();

    bool get_grip() const;

    void move(float x, float y, float z);

private:
    float _x;
    float _y;
    float _z;
    bool _grip;
};