#include "player.hpp"

Player::Player() : _life(5), _score(0)
{
}

int Player::get_life() const
{
    return _life;
}

int Player::get_score() const
{
    return _score;
}

void Player::set_life(int life)
{
    _life = life;
}

void Player::add_score(int score)
{
    _score += score;
}

void Player::display_score(const TextureObject &texture) const
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.get_width(), texture.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture.get_image());
    glPushMatrix();
    glColor3f(1., 1., 1.);
    glRotatef(-90, 1., 0., 0.);
    glRotatef(-90, 0., 1., 0.);
    glEnable(GL_TEXTURE_2D);
    drawSquareTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Player::drawPlayer(const TextureObject &texture0, const TextureObject &texture1, const TextureObject &texture2, const TextureObject &texture3, const TextureObject &texture4, const TextureObject &texture5, const TextureObject &texture6, const TextureObject &texture7, const TextureObject &texture8, const TextureObject &texture9, const Ball &life_ball, const TextureObject &texture_ball) const
{
    for (int i = 0; i < _life; i++)
    {
        glPushMatrix();
        glTranslatef(0., -8.0 + 1.2 * i, -8.0);
        glScalef(0.5, 0.5, 0.5);
        glColor3f(1.0, 0.0, 0.0);
        life_ball.drawTex(texture_ball);
        glPopMatrix();
    }
    // display score
    int score = _score;
    int digit = 0;
    int digits = 0;
    while (score > 0)
    {
        digit = score % 10;
        score /= 10;
        glPushMatrix();
        glTranslatef(0., 8. - 0.8 * digits, 8.);
        switch (digit)
        {
        case 0:
            display_score(texture0);
            break;
        case 1:
            display_score(texture1);
            break;
        case 2:
            display_score(texture2);
            break;
        case 3:
            display_score(texture3);
            break;
        case 4:
            display_score(texture4);
            break;
        case 5:
            display_score(texture5);
            break;
        case 6:
            display_score(texture6);
            break;
        case 7:
            display_score(texture7);
            break;
        case 8:
            display_score(texture8);
            break;
        case 9:
            display_score(texture9);
            break;
        default:
            break;
        }
        glPopMatrix();
        digits++;
    }
}

void Player::drawScore(const TextureObject &texture0, const TextureObject &texture1, const TextureObject &texture2, const TextureObject &texture3, const TextureObject &texture4, const TextureObject &texture5, const TextureObject &texture6, const TextureObject &texture7, const TextureObject &texture8, const TextureObject &texture9) const
{
    // display score
    int score = _score;
    int digit = 0;
    int digits = 0;
    while (score > 0)
    {
        digit = score % 10;
        score /= 10;
        glPushMatrix();
        glTranslatef(0., 0. - 0.8 * digits, 0.);
        switch (digit)
        {
        case 0:
            display_score(texture0);
            break;
        case 1:
            display_score(texture1);
            break;
        case 2:
            display_score(texture2);
            break;
        case 3:
            display_score(texture3);
            break;
        case 4:
            display_score(texture4);
            break;
        case 5:
            display_score(texture5);
            break;
        case 6:
            display_score(texture6);
            break;
        case 7:
            display_score(texture7);
            break;
        case 8:
            display_score(texture8);
            break;
        case 9:
            display_score(texture9);
            break;
        default:
            break;
        }
        glPopMatrix();
        digits++;
    }
}

void Player::reset()
{
    _life = 5;
    _score = 0;
}