#pragma once

#include "drawable.hpp"

class Obstacle : public Drawable
{
public:
    Obstacle(float depth);

    void draw() override;

    void move(float delta);

    bool has_to_despawn() const { return _has_to_despawn; }

private:
    float _depth = -40.0;
    bool _has_to_despawn = false;
};
