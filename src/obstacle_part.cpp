#include "obstacle_part.hpp"

ObstaclePart::ObstaclePart()
{
}

ObstaclePart::ObstaclePart(float y, float z, float speed_y, float speed_z, float scale_y, float scale_z, float scale_speed_y, float scale_speed_z)
    : _y(y),
      _z(z),
      _speed_y(speed_y),
      _speed_z(speed_z),
      _scale_y(scale_y),
      _scale_z(scale_z),
      _scale_speed_y(scale_speed_y),
      _scale_speed_z(scale_speed_z)
{
}

void ObstaclePart::draw() const
{
    glPushMatrix();
    glTranslatef(_z, _y, 0.0);
    glScalef(_scale_z, _scale_y, 1.0);
    drawSquare();
    glPopMatrix();
}

bool ObstaclePart::collide(Ball &ball, float depth)
{
    float ball_x, ball_y, ball_z;
    ball.get_position(ball_x, ball_y, ball_z);
    float ball_x_speed, ball_y_speed, ball_z_speed;
    ball.get_speed(ball_x_speed, ball_y_speed, ball_z_speed);

    float x = std::max(depth, std::min(ball_x, depth));
    float y = std::max(_y - _scale_y / 2.0f, std::min(ball_y, _y + _scale_y / 2.0f));
    float z = std::max(_z - _scale_z / 2.0f, std::min(ball_z, _z + _scale_z / 2.0f));

    float distance = std::sqrt((x - ball_x) * (x - ball_x) + (y - ball_y) * (y - ball_y) + (z - ball_z) * (z - ball_z));

    if (distance < 1.0)
    {
        ball.set_speed(-ball_x_speed, ball_y_speed, ball_z_speed);
        return true;
    }
    return false;
}

bool ObstaclePart::do_collide(Racket &racket) const
{
    float racket_x, racket_y, racket_z;
    racket.get_position(racket_x, racket_y, racket_z);
    float racket_scale_x, racket_scale_y;
    racket.get_scale(racket_scale_x, racket_scale_y);

    float racket_left = racket_x - racket_scale_x / 2.0f;
    float racket_right = racket_x + racket_scale_x / 2.0f;
    float racket_top = racket_y + racket_scale_y / 2.0f;
    float racket_bottom = racket_y - racket_scale_y / 2.0f;

    float obstacle_left = _z - _scale_z / 2.0f;
    float obstacle_right = _z + _scale_z / 2.0f;
    float obstacle_top = _y + _scale_y / 2.0f;
    float obstacle_bottom = _y - _scale_y / 2.0f;

    if (racket_right >= obstacle_left && racket_left <= obstacle_right &&
        racket_top >= obstacle_bottom && racket_bottom <= obstacle_top)
    {
        return true;
    }

    return false;
}

void ObstaclePart::evolve()
{
    _y += _speed_y;
    _z += _speed_z;
    _scale_y += _scale_speed_y;
    _scale_z += _scale_speed_z;
    if (_scale_y <= 0.1)
    {
        _scale_speed_y = -_scale_speed_y;
    }
    if (_scale_z <= 0.1)
    {
        _scale_speed_z = -_scale_speed_z;
    }
}

void ObstaclePart::get_position(float &y, float &z) const
{
    y = _y;
    z = _z;
}

void ObstaclePart::get_scale(float &y, float &z) const
{
    y = _scale_y;
    z = _scale_z;
}

void ObstaclePart::get_speed(float &speed_y, float &speed_z) const
{
    speed_y = _speed_y;
    speed_z = _speed_z;
}

void ObstaclePart::set_speed(float speed_y, float speed_z)
{
    _speed_y = speed_y;
    _speed_z = speed_z;
}

void ObstaclePart::get_scale_speed(float &speed_y, float &speed_z) const
{
    speed_y = _scale_speed_y;
    speed_z = _scale_speed_z;
}

void ObstaclePart::set_scale_speed(float speed_y, float speed_z)
{
    _scale_speed_y = speed_y;
    _scale_speed_z = speed_z;
}