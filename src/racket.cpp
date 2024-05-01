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
    glScalef(_scale_x, _scale_y, 1.);
    drawEmptySquare();
    glPopMatrix();
}

void Racket::move(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

void Racket::collide(Ball &ball)
{
    float ball_x, ball_y, ball_z;
    ball.get_position(ball_x, ball_y, ball_z);
    float ball_x_speed, ball_y_speed, ball_z_speed;
    ball.get_speed(ball_x_speed, ball_y_speed, ball_z_speed);

    if (ball_x_speed < 0)
    {
        return;
    }

    float x = std::max(_z, std::min(ball_x, _z));
    float y = std::max(_y - _scale_y / 2.0f, std::min(ball_y, _y + _scale_y / 2.0f));
    float z = std::max(-_x - _scale_x / 2.0f, std::min(ball_z, -_x + _scale_x / 2.0f));

    float distance = std::sqrt((x - ball_x) * (x - ball_x) + (y - ball_y) * (y - ball_y) + (z - ball_z) * (z - ball_z));

    if (distance < 1.0)
    {
        float collision_distance_y = y - _y;
        float collision_distance_z = z + _x;
        ball.set_speed(-ball_x_speed, collision_distance_y / 10.0, collision_distance_z / 10.0);
    }
}
