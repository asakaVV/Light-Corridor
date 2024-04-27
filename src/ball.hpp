#pragma once

#include "drawable.hpp"

class Ball : public Drawable
{
public:
    Ball();

    void draw() override;
};