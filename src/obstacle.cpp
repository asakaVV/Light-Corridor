#include "obstacle.hpp"

Obstacle::Obstacle(float depth, float obstacle_depth) : _depth(depth)
{
    ObstaclePart part = ObstaclePart(5.0, 0.0, -0.1, 0.0, 10.0, 12.0, 0.0, -0.1);
    _parts.push_back(part);
    ObstaclePart part2 = ObstaclePart(0.0, 0.0, 0.0, 0.0, 15.0, 1.0, 0.0, 0.0);
    _parts.push_back(part2);
}

void Obstacle::draw() const
{
    glPushMatrix();
    glTranslatef(_depth, 0.0, 0.0);
    glScalef(10.0, 19.9, 11.9);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    drawEmptySquare();
    glPopMatrix();

    GLfloat light_spec[] = {1.0, 1.0, 1.0};
    GLfloat amb[] = {0., 0., 0.};
    GLfloat color[] = {0.0, 1.0, 0.0};
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.);
    glTranslatef(_depth, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    // glColor3f(0.0, 1.0, 0.0);
    for (const auto &part : _parts)
    {
        part.draw();
    }
    glColor3f(1., 1., 1.);
    glPopMatrix();
}

bool Obstacle::move(float delta)
{
    _depth += delta;
    if (_depth > -0.0)
    {
        _has_to_despawn = true;
        return true;
    }
    return false;
}

void Obstacle::collide(Ball &ball)
{
    for (auto &part : _parts)
    {
        if (part.collide(ball, _depth))
        {
            return;
        }
    }
}

bool Obstacle::do_collide(Racket &racket) const
{
    for (const auto &part : _parts)
    {
        if (_depth > -1 && part.do_collide(racket))
        {
            return true;
        }
    }

    return false;
}

bool Obstacle::do_any_collide(const std::vector<Obstacle> &obstacles, Racket &racket)
{
    for (const auto &obstacle : obstacles)
    {
        if (obstacle.do_collide(racket))
        {
            return true;
        }
    }

    return false;
}

void Obstacle::evolve()
{
    for (auto &part : _parts)
    {
        part.evolve();
    }
}

void Obstacle::collide(Wall &wall)
{
    for (auto &part : _parts)
    {
        wall.collide(part);
    }
}
