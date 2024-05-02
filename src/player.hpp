#pragma once

#include "texture.hpp"
#include "drawable.hpp"
#include "ball.hpp"

class Player
{
public:
    Player();
    int get_life() const;
    int get_score() const;
    void set_life(int life);
    void add_score(int score);
    void display_score(const TextureObject &texture) const;
    void drawPlayer(const TextureObject &texture_0, const TextureObject &texture1, const TextureObject &texture2, const TextureObject &texture3, const TextureObject &texture4, const TextureObject &texture5, const TextureObject &texture6, const TextureObject &texture7, const TextureObject &texture8, const TextureObject &texture9, const Ball &life_ball, const TextureObject &texture_ball) const;

private:
    int _life;
    int _score;
};