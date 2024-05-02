#include "player.hpp"

Player::Player() : _life(5), _score(0)
{
}

int Player::get_life() const
{
    return _life;
}

int Player::get_score() const
{
    return _score;
}

void Player::set_life(int life)
{
    _life = life;
}

void Player::add_score(int score)
{
    _score += score;
}