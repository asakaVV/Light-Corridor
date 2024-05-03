#pragma once

#include "drawable.hpp"
#include "racket.hpp"

class Bonus : public Drawable
{
public:
    Bonus(float x, float y, float z, int type);

    void draw() const override;

    void move(float delta);

    void get_position(float &x, float &y, float &z) const;

    int get_type() const;

    float get_x() const { return _x; }

    int collide(const Racket &racket);

private:
    float _x;
    float _y;
    float _z;
    int _type;
};