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

void Ball::set_grip(bool grip)
{
    _grip = grip;
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

void Ball::set_speed(float x, float y, float z)
{
    _x_speed = x;
    _y_speed = y;
    _z_speed = z;
}

void Ball::get_speed(float &x, float &y, float &z) const
{
    x = _x_speed;
    y = _y_speed;
    z = _z_speed;
}

void Ball::update()
{
    _x += _x_speed;
    _y += _y_speed;
    _z += _z_speed;
}

void Ball::move_with_delta(float delta)
{
    _x += delta;
}

void Ball::get_position(float &x, float &y, float &z) const
{
    x = _x;
    y = _y;
    z = _z;
}