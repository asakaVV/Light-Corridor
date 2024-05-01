#pragma once

#include "drawable.hpp"
#include "ball.hpp"
#include "racket.hpp"

class ObstaclePart : public Drawable
{
public:
    ObstaclePart();

    ObstaclePart(float y, float z, float speed_y, float speed_z, float scale_y, float scale_z, float scale_speed_y, float scale_speed_z);

    void draw() const override;

    bool collide(Ball &ball, float depth);

    bool do_collide(Racket &racket) const;

    void evolve();

    void get_position(float &y, float &z) const;

    void get_scale(float &y, float &z) const;

    void get_speed(float &speed_y, float &speed_z) const;

    void set_speed(float speed_y, float speed_z);

    void get_scale_speed(float &speed_y, float &speed_z) const;

    void set_scale_speed(float speed_y, float speed_z);

private:
    float _y = 5.0;
    float _z = 0.0;
    float _speed_y = 0.0;
    float _speed_z = 0.0;
    float _scale_y = 10.0;
    float _scale_z = 12.0;
    float _scale_speed_y = 0.0;
    float _scale_speed_z = 0.0;
};
