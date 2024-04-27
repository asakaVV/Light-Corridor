#include "wall.hpp"

Wall::Wall(std::vector<float> center, std::vector<float> size, float rotation, std::vector<float> color)
{
    _center[0] = center[0];
    _center[1] = center[1];
    _center[2] = center[2];
    _size[0] = size[0];
    _size[1] = size[1];
    _size[2] = size[2];
    _rotation = rotation;
    _color[0] = color[0];
    _color[1] = color[1];
    _color[2] = color[2];
}

void Wall::draw()
{
    glPushMatrix();
    glTranslatef(_center[0], _center[1], _center[2]);
    glScalef(_size[0], _size[1], _size[2]);
    glRotatef(_rotation, 1.0, 0.0, 0.0);
    glColor3f(_color[0], _color[1], _color[2]);
    drawSquare();
    glPopMatrix();
}
