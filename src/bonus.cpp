#include "bonus.hpp"

Bonus::Bonus(float x, float y, float z, int type)
    : _x(x), _y(y), _z(z), _type(type)
{
}

void Bonus::draw() const
{
    if (_type == 0)
    {
        return;
    }
    GLfloat light_spec[] = {1.0, 1.0, 1.0};
    GLfloat amb[] = {0., 0., 0.};
    GLfloat color[] = {0., 0., 0.};
    if (_type == 1)
    {
        color[0] = 1.;
    }
    else if (_type == 2)
    {
        color[0] = 1.;
        color[1] = 1.;
        color[2] = 1.;
    }
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.);
    glTranslatef(_x, _y, _z);
    drawCube();
    glPopMatrix();
}

void Bonus::move(float delta)
{
    _x += delta;
}

void Bonus::get_position(float &x, float &y, float &z) const
{
    x = _x;
    y = _y;
    z = _z;
}

int Bonus::get_type() const
{
    return _type;
}

int Bonus::collide(const Racket &racket)
{
    if (_x >= 0.)
    {
        float racket_x, racket_y, racket_z;
        racket.get_position(racket_x, racket_y, racket_z);
        float racket_scale_x, racket_scale_y;
        racket.get_scale(racket_scale_x, racket_scale_y);

        float racket_top = -(racket_x - racket_scale_x / 2.0f);
        float racket_bottom = -(racket_x + racket_scale_x / 2.0f);
        float racket_right = racket_y + racket_scale_y / 2.0f;
        float racket_left = racket_y - racket_scale_y / 2.0f;

        if (racket_right >= _y + 0.5 && racket_left <= _y + 0.5 &&
            racket_top >= _z - 0.5 && racket_bottom <= _z - 0.5)
        {
            int type = _type;
            _type = 0;
            return type;
        }
    }

    return 0;
}
