#include "ball.hpp"

Ball::Ball()
    : _x(0.0), _y(0.0), _z(0.0)
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