#pragma once

#include "drawable.hpp"

class Racket : public Drawable
{
public:
    Racket();

    void move(float x, float y, float z);

    void draw() const override;

private:
    float _x;
    float _y;
    float _z;
};