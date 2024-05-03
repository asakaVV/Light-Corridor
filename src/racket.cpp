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

bool Racket::collide(Ball &ball)
{
    float ball_x, ball_y, ball_z;
    ball.get_position(ball_x, ball_y, ball_z);
    float ball_x_speed, ball_y_speed, ball_z_speed;
    ball.get_speed(ball_x_speed, ball_y_speed, ball_z_speed);

    if (ball_x_speed < 0)
    {
        return false;
    }

    bool negative = false;
    if (ball_x > 0 && ball_y > _y - _scale_y / 2.0f && ball_y < _y + _scale_y / 2.0f && ball_z > -_x - _scale_x / 2.0f && ball_z < -_x + _scale_x / 2.0f)
    {
        negative = true;
        float time = (ball_x) / ball_x_speed;
        ball_x -= time * ball_x_speed;
        ball_y -= time * ball_y_speed;
        ball_z -= time * ball_z_speed;
    }

    float x = std::max(_z, std::min(ball_x, _z));
    float y = std::max(_y - _scale_y / 2.0f, std::min(ball_y, _y + _scale_y / 2.0f));
    float z = std::max(-_x - _scale_x / 2.0f, std::min(ball_z, -_x + _scale_x / 2.0f));

    float distance = std::sqrt((x - ball_x) * (x - ball_x) + (y - ball_y) * (y - ball_y) + (z - ball_z) * (z - ball_z));

    if (distance < 1.0)
    {
        ball_x_speed = std::min(2.0, ball_x_speed + 0.02);

        float collision_distance_y = y - _y;
        float collision_distance_z = z + _x;

        float initial_speed = std::sqrt(ball_x_speed * ball_x_speed + ball_y_speed * ball_y_speed + ball_z_speed * ball_z_speed);

        float new_ball_x_speed = -ball_x_speed;
        float new_ball_y_speed = collision_distance_y / 5.0;
        float new_ball_z_speed = collision_distance_z / 5.0;

        float new_speed_magnitude = std::sqrt(new_ball_x_speed * new_ball_x_speed + new_ball_y_speed * new_ball_y_speed + new_ball_z_speed * new_ball_z_speed);
        new_ball_x_speed /= new_speed_magnitude;
        new_ball_y_speed /= new_speed_magnitude;
        new_ball_z_speed /= new_speed_magnitude;

        new_ball_x_speed *= initial_speed;
        new_ball_y_speed *= initial_speed;
        new_ball_z_speed *= initial_speed;

        ball.set_speed(new_ball_x_speed, new_ball_y_speed, new_ball_z_speed);

        if (negative)
        {
            ball.move(-1.1, ball_y, ball_z);
        }

        return true;
    }
    return false;
}

void Racket::get_position(float &x, float &y, float &z) const
{
    x = _x;
    y = _y;
    z = _z;
}

void Racket::get_scale(float &x, float &y) const
{
    x = _scale_x;
    y = _scale_y;
}
