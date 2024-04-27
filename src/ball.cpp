#include "ball.hpp"

Ball::Ball()
{
}

void Ball::draw()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    drawSphere();
    glPopMatrix();
}