#include "obstacle_part.hpp"

ObstaclePart::ObstaclePart()
{
}

void ObstaclePart::draw() const
{
    glPushMatrix();
    glTranslatef(_z, _y, 0.0);
    glRotatef(_rotation, 0.0, 0.0, 1.0);
    glScalef(_scale_z, _scale_y, 1.0);
    drawSquare();
    glPopMatrix();
}

void ObstaclePart::collide(Ball &ball, float depth)
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
    }
}
