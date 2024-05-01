#include "racket.hpp"

Racket::Racket()
    : _x(0.0), _y(0.0), _z(0.0)
{
}

void Racket::draw() const
{
    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(_x, _y, _z);
    glColor3f(1.0, 1.0, 1.0);
    glScalef(4., 4., 1.);
    drawEmptySquare();
    glPopMatrix();
}

void Racket::move(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}