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