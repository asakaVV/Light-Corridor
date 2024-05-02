#pragma once

class Player
{
public:
    Player();
    int get_life() const;
    int get_score() const;
    void set_life(int life);
    void add_score(int score);

private:
    int _life;
    int _score;
};