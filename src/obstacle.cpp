#include "obstacle.hpp"

Obstacle::Obstacle(float depth) : _depth(depth)
{
    ObstaclePart part;
    _parts.push_back(part);
}

void Obstacle::draw() const
{
    glPushMatrix();
    glTranslatef(_depth, 0.0, 0.0);
    glScalef(10.0, 19.9, 11.9);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    drawEmptySquare();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(_depth, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    for (const auto &part : _parts)
    {
        part.draw();
    }
    glPopMatrix();
}

void Obstacle::move(float delta)
{
    _depth += delta;
    if (_depth > 0.0)
    {
        _has_to_despawn = true;
    }
}

void Obstacle::collide(Ball &ball)
{
    for (auto &part : _parts)
    {
        part.collide(ball, _depth);
    }
}

bool Obstacle::do_collide(Racket &racket) const
{
    for (const auto &part : _parts)
    {
        if (_depth > -0.5 && part.do_collide(racket))
        {
            return true;
        }
    }

    return false;
}

bool Obstacle::do_any_collide(const std::vector<Obstacle> &obstacles, Racket &racket)
{
    for (const auto &obstacle : obstacles)
    {
        if (obstacle.do_collide(racket))
        {
            return true;
        }
    }

    return false;
}