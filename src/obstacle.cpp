#include "obstacle.hpp"

Obstacle::Obstacle(float depth, long level) : _depth(depth)
{
    float floor = std::sqrt(level);

    // Obstacle or Not
    if (Random::get_int(1, 100) <= std::max(0, (int)((100 - floor * 3) - 40)))
    {
        return;
    }

    int obstacle_type = Random::get_int(1, std::min(13, (int)floor));

    int type;

    switch (obstacle_type)
    {
    case 1: // Half
        type = Random::get_int(1, 4);
        switch (type)
        {
        case 1: // Right
            _parts.push_back(ObstaclePart(5.0, 0.0, 0.0, 0.0, 10.0, 12.0, 0.0, 0.0));
            break;
        case 2: // Left
            _parts.push_back(ObstaclePart(-5.0, 0.0, 0.0, 0.0, 10.0, 12.0, 0.0, 0.0));
            break;
        case 3: // Top
            _parts.push_back(ObstaclePart(0.0, 3.0, 0.0, 0.0, 20.0, 6.0, 0.0, 0.0));
            break;
        case 4: // Bottom
            _parts.push_back(ObstaclePart(0.0, -3.0, 0.0, 0.0, 20.0, 6.0, 0.0, 0.0));
            break;
        }
        break;
    case 2: // Corner
        type = Random::get_int(1, 4);
        switch (type)
        {
        case 1: // Bottom Right
            _parts.push_back(ObstaclePart(-7.5, 0.0, 0.0, 0.0, 5.0, 12.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(0.0, -4.5, 0.0, 0.0, 20.0, 3.0, 0.0, 0.0));
            break;
        case 2: // Bottom Left
            _parts.push_back(ObstaclePart(7.5, 0.0, 0.0, 0.0, 5.0, 12.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(0.0, -4.5, 0.0, 0.0, 20.0, 3.0, 0.0, 0.0));
            break;
        case 3: // Top Left
            _parts.push_back(ObstaclePart(7.5, 0.0, 0.0, 0.0, 5.0, 12.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(0.0, 4.5, 0.0, 0.0, 20.0, 3.0, 0.0, 0.0));
            break;
        case 4: // Top Right
            _parts.push_back(ObstaclePart(-7.5, 0.0, 0.0, 0.0, 5.0, 12.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(0.0, 4.5, 0.0, 0.0, 20.0, 3.0, 0.0, 0.0));
            break;
        }
        break;
    case 3: // Chess
        type = Random::get_int(1, 2);
        switch (type)
        {
        case 1: // 1
            _parts.push_back(ObstaclePart(5.0, 3.0, 0.0, 0.0, 10.0, 6.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-5.0, -3.0, 0.0, 0.0, 10.0, 6.0, 0.0, 0.0));
            break;
        case 2: // 2
            _parts.push_back(ObstaclePart(5.0, -3.0, 0.0, 0.0, 10.0, 6.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-5.0, 3.0, 0.0, 0.0, 10.0, 6.0, 0.0, 0.0));
            break;
        }
        break;
    case 4: // Small
        _parts.push_back(ObstaclePart(-7.5, 0.0, 0.0, 0.0, 5.0, 12.0, 0.0, 0.0));
        _parts.push_back(ObstaclePart(0.0, -4.5, 0.0, 0.0, 20.0, 3.0, 0.0, 0.0));
        _parts.push_back(ObstaclePart(7.5, 0.0, 0.0, 0.0, 5.0, 12.0, 0.0, 0.0));
        _parts.push_back(ObstaclePart(0.0, 4.5, 0.0, 0.0, 20.0, 3.0, 0.0, 0.0));
        break;
    case 5: // Anti Corner
        type = Random::get_int(1, 4);
        switch (type)
        {
        case 1: // Bottom Right
            _parts.push_back(ObstaclePart(2.25, 2.25, 0.0, 0.0, 15.5, 7.5, 0.0, 0.0));
            break;
        case 2: // Bottom Left
            _parts.push_back(ObstaclePart(-2.25, 2.25, 0.0, 0.0, 15.5, 7.5, 0.0, 0.0));
            break;
        case 3: // Top Left
            _parts.push_back(ObstaclePart(-2.25, -2.25, 0.0, 0.0, 15.5, 7.5, 0.0, 0.0));
            break;
        case 4: // Top Right
            _parts.push_back(ObstaclePart(2.25, -2.25, 0.0, 0.0, 15.5, 7.5, 0.0, 0.0));
            break;
        }
        break;
    case 6: // Cross
        _parts.push_back(ObstaclePart(0.0, 0.0, 0.0, 0.0, 20.0, 3.0, 0.0, 0.0));
        _parts.push_back(ObstaclePart(0.0, 0.0, 0.0, 0.0, 7.0, 12.0, 0.0, 0.0));
        break;
    case 7: // Sizing Center
        _parts.push_back(ObstaclePart(0.0, 0.0, 0.0, 0.0, 10.0, 6.0, 0.2, 0.2));
        break;
    case 8: // Sizing Sides
        _parts.push_back(ObstaclePart(-5.0, 0.0, 0.0, 0.0, 10.0, 12.0, -0.1, -0.12));
        _parts.push_back(ObstaclePart(5.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.12));
        break;
    case 9: // Sizing Corners
        _parts.push_back(ObstaclePart(5.0, 3.0, 0.0, 0.0, 0.1, 0.1, 0.125, 0.069));
        _parts.push_back(ObstaclePart(-5.0, 3.0, 0.0, 0.0, 10.0, 6.0, -0.125, -0.069));
        _parts.push_back(ObstaclePart(-5.0, -3.0, 0.0, 0.0, 0.1, 0.1, 0.125, 0.069));
        _parts.push_back(ObstaclePart(5.0, -3.0, 0.0, 0.0, 10.0, 6.0, -0.125, -0.069));
        break;
    case 10: // Moving Half
        type = Random::get_int(1, 4);
        switch (type)
        {
        case 1: // Right
            _parts.push_back(ObstaclePart(5.0, 0.0, 0.2, 0.0, 10.0, 12.0, 0.0, 0.0));
            break;
        case 2: // Left
            _parts.push_back(ObstaclePart(-5.0, 0.0, 0.2, 0.0, 10.0, 12.0, 0.0, 0.0));
            break;
        case 3: // Top
            _parts.push_back(ObstaclePart(0.0, 3.0, 0.0, 0.1, 20.0, 6.0, 0.0, 0.0));
            break;
        case 4: // Bottom
            _parts.push_back(ObstaclePart(0.0, -3.0, 0.0, 0.1, 20.0, 6.0, 0.0, 0.0));
            break;
        }
        break;
    case 11: // Stairs
        type = Random::get_int(1, 4);
        switch (type)
        {
        case 1: // From Top Left
            _parts.push_back(ObstaclePart(-9.0, -5.0, 0.05, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-7.0, -3.0, 0.1, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-5.0, -1.0, 0.15, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-3.0, 1.0, 0.2, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-1.0, 3.0, 0.25, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(1.0, 5.0, 0.3, 0.0, 2.0, 2.0, 0.0, 0.0));
            break;
        case 2: // From Bottom Right
            _parts.push_back(ObstaclePart(9.0, 5.0, -0.05, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(7.0, 3.0, -0.1, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(5.0, 1.0, -0.15, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(3.0, -1.0, -0.2, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(1.0, -3.0, -0.25, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-1.0, -5.0, -0.3, 0.0, 2.0, 2.0, 0.0, 0.0));
            break;
        case 3: // From Top Right
            _parts.push_back(ObstaclePart(9.0, -5.0, 0.05, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(7.0, -3.0, 0.1, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(5.0, -1.0, 0.15, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(3.0, 1.0, 0.2, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(1.0, 3.0, 0.25, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-1.0, 5.0, 0.3, 0.0, 2.0, 2.0, 0.0, 0.0));
            break;
        case 4: // From Bottom Left
            _parts.push_back(ObstaclePart(-9.0, 5.0, -0.05, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-7.0, 3.0, -0.1, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-5.0, 1.0, -0.15, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-3.0, -1.0, -0.2, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(-1.0, -3.0, -0.25, 0.0, 2.0, 2.0, 0.0, 0.0));
            _parts.push_back(ObstaclePart(1.0, -5.0, -0.3, 0.0, 2.0, 2.0, 0.0, 0.0));
            break;
        }
        break;
    case 12: // Double Moving And Sizing
        _parts.push_back(ObstaclePart(0.0, 0.0, 0.0, 0.0, 20.0, 6.0, 0.0, 0.1));
        _parts.push_back(ObstaclePart(0.0, -3.0, 0.1, 0.0, 7.0, 6.0, 0.0, 0.0));
        _parts.push_back(ObstaclePart(0.0, 3.0, -0.1, 0.0, 7.0, 6.0, 0.0, 0.0));
        break;
    case 13: // Slider
        _parts.push_back(ObstaclePart(0.0, 0.0, 0.0, 0.0, 20.0, 1.0, 0.0, 0.0));
        _parts.push_back(ObstaclePart(0.0, 0.0, 0.1, 0.0, 10.0, 12.0, 0.0, 0.1));
        break;
    }
}

void Obstacle::draw() const
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(_depth, 0.0, 0.0);
    glScalef(10.0, 19.9, 11.9);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    drawEmptySquare();
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_LIGHTING);

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

bool Obstacle::do_collide(Racket &racket, float limit) const
{
    for (const auto &part : _parts)
    {
        if (_depth > limit && part.do_collide(racket))
        {
            return true;
        }
    }

    return false;
}

bool Obstacle::do_any_collide(const std::vector<Obstacle> &obstacles, Racket &racket, float limit)
{
    for (const auto &obstacle : obstacles)
    {
        if (obstacle.do_collide(racket, limit))
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
