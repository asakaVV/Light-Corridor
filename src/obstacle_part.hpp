#pragma once

#include "drawable.hpp"
#include "ball.hpp"
#include "racket.hpp"

class ObstaclePart : public Drawable
{
public:
    ObstaclePart();

    void draw() const override;

    void collide(Ball &ball, float depth);

    bool do_collide(Racket &racket) const;

private:
    float _y = 5.0;
    float _z = 0.0;
    // float _speed_y = 0.0;
    // float _speed_z = 0.0;
    float _rotation = 0.0;
    // float _rotation_speed = 0.0;
    float _scale_y = 10.0;
    float _scale_z = 12.0;
    // float _scale_speed_y = 0.0;
    // float _scale_speed_z = 0.0;
};
