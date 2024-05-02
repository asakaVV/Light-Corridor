#pragma once

#include "drawable.hpp"
#include "obstacle_part.hpp"
#include "ball.hpp"
#include "racket.hpp"
#include "wall.hpp"
#include "random.hpp"
#include <vector>

class Obstacle : public Drawable
{
public:
    Obstacle(float depth, long level);

    void draw() const override;

    bool move(float delta);

    bool has_to_despawn() const { return _has_to_despawn; }

    void collide(Ball &ball);

    bool do_collide(Racket &racket, float limit) const;

    static bool do_any_collide(const std::vector<Obstacle> &obstacles, Racket &racket, float limit);

    void evolve();

    void collide(Wall &wall);

    float get_depth() const { return _depth; }

private:
    float _depth = -40.0;
    bool _has_to_despawn = false;
    std::vector<ObstaclePart> _parts;
};
