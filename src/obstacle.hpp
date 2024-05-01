#pragma once

#include "drawable.hpp"
#include "obstacle_part.hpp"
#include "ball.hpp"
#include "racket.hpp"
#include <vector>

class Obstacle : public Drawable
{
public:
    Obstacle(float depth);

    void draw() const override;

    void move(float delta);

    bool has_to_despawn() const { return _has_to_despawn; }

    void collide(Ball &ball);

    bool do_collide(Racket &racket) const;

    static bool do_any_collide(const std::vector<Obstacle> &obstacles, Racket &racket);

private:
    float _depth = -40.0;
    bool _has_to_despawn = false;
    std::vector<ObstaclePart> _parts;
};
