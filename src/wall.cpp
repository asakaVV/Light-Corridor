#include "wall.hpp"

Wall::Wall(std::vector<float> center, std::vector<float> size, float rotation, std::vector<float> color, WallType type)
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
    _type = type;
}

void Wall::draw() const
{
    glPushMatrix();
    glTranslatef(_center[0], _center[1], _center[2]);
    glScalef(_size[0], _size[1], _size[2]);
    glRotatef(_rotation, 1.0, 0.0, 0.0);
    glColor3f(_color[0], _color[1], _color[2]);
    drawSquare();
    glPopMatrix();
}

void Wall::collide(Ball &ball)
{
    float ball_x, ball_y, ball_z;
    ball.get_position(ball_x, ball_y, ball_z);
    float ball_x_speed, ball_y_speed, ball_z_speed;
    ball.get_speed(ball_x_speed, ball_y_speed, ball_z_speed);

    switch (_type)
    {
    case WallType::TOP:
        if (ball_z + 1.0 >= _center[2])
        {
            ball.set_speed(ball_x_speed, ball_y_speed, -ball_z_speed);
        }
        break;
    case WallType::LEFT:
        if (ball_y - 1.0 <= _center[1])
        {
            ball.set_speed(ball_x_speed, -ball_y_speed, ball_z_speed);
        }
        break;
    case WallType::RIGHT:
        if (ball_y + 1.0 >= _center[1])
        {
            ball.set_speed(ball_x_speed, -ball_y_speed, ball_z_speed);
        }
        break;
    case WallType::BOTTOM:
        if (ball_z - 1.0 <= _center[2])
        {
            ball.set_speed(ball_x_speed, ball_y_speed, -ball_z_speed);
        }
        break;
    }
}

void Wall::collide(ObstaclePart &part)
{
    float part_y, part_z;
    part.get_position(part_y, part_z);
    float part_scale_y, part_scale_z;
    part.get_scale(part_scale_y, part_scale_z);
    float part_speed_y, part_speed_z;
    part.get_speed(part_speed_y, part_speed_z);
    float part_scale_speed_y, part_scale_speed_z;
    part.get_scale_speed(part_scale_speed_y, part_scale_speed_z);

    float part_left = part_z - part_scale_z / 2.0f;
    float part_right = part_z + part_scale_z / 2.0f;
    float part_top = part_y + part_scale_y / 2.0f;
    float part_bottom = part_y - part_scale_y / 2.0f;

    switch (_type)
    {
    case WallType::TOP:
        if ((part_speed_z > 0 || part_scale_speed_z > 0) && part_top >= _center[1] - _size[1] / 2.0f && part_bottom <= _center[1] + _size[1] / 2.0f && part_right >= _center[2] - _size[2] / 2.0f && part_left <= _center[2] + _size[2] / 2.0f)
        {
            part.set_speed(part_speed_y, -part_speed_z);
            part.set_scale_speed(part_scale_speed_y, -part_scale_speed_z);
        }
        break;
    case WallType::LEFT:
        if ((part_speed_y < 0 || part_scale_speed_y > 0) && part_right >= _center[2] - _size[2] / 2.0f && part_left <= _center[2] + _size[2] / 2.0f && part_top >= _center[1] - _size[1] / 2.0f && part_bottom <= _center[1] + _size[1] / 2.0f)
        {
            part.set_speed(-part_speed_y, part_speed_z);
            part.set_scale_speed(-part_scale_speed_y, part_scale_speed_z);
        }
        break;
    case WallType::RIGHT:
        if ((part_speed_y > 0 || part_scale_speed_y > 0) && part_right >= _center[2] - _size[2] / 2.0f && part_left <= _center[2] + _size[2] / 2.0f && part_top >= _center[1] - _size[1] / 2.0f && part_bottom <= _center[1] + _size[1] / 2.0f)
        {
            part.set_speed(-part_speed_y, part_speed_z);
            part.set_scale_speed(-part_scale_speed_y, part_scale_speed_z);
        }
        break;
    case WallType::BOTTOM:
        if ((part_speed_z < 0 || part_scale_speed_z > 0) && part_top >= _center[1] - _size[1] / 2.0f && part_bottom <= _center[1] + _size[1] / 2.0f && part_right >= _center[2] - _size[2] / 2.0f && part_left <= _center[2] + _size[2] / 2.0f)
        {
            part.set_speed(part_speed_y, -part_speed_z);
            part.set_scale_speed(part_scale_speed_y, -part_scale_speed_z);
        }
        break;
    }
}
