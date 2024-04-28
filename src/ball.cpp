#include "ball.hpp"

Ball::Ball()
    : _x(0.0), _y(0.0), _z(0.0), _grip(true)
{
}

void Ball::draw()
{
    glPushMatrix();
    glTranslatef(_x - 1., _y, _z);
    glColor3f(1.0, 0.0, 0.0);
    drawSphere();
    glPopMatrix();
}

void Ball::change_grip()
{
    _grip = !_grip;
}

bool Ball::get_grip() const
{
    return _grip;
}

void Ball::move(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}