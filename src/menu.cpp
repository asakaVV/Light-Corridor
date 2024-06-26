#include "menu.hpp"

void draw_scene()
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
}

void draw_button(const TextureObject &texture)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.get_width(), texture.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture.get_image());
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-2., -1., 0);
    glVertex3f(-2., 1., 0);
    glVertex3f(2., 1., 0);
    glVertex3f(2., -1., 0);
    glEnd();
    glPushMatrix();
    {
        glTranslatef(-1.82, -0.9, 0.1);
        glColor3f(1., 1., 1);
        glScalef(3.7, 1.8, 1.);
        glEnable(GL_TEXTURE_2D);
        drawSquareTex();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void draw_hover_button(const TextureObject &texture)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.get_width(), texture.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture.get_image());
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-2., -1., 0);
    glVertex3f(-2., 1., 0);
    glVertex3f(2., 1., 0);
    glVertex3f(2., -1., 0);
    glEnd();
    glPushMatrix();
    {
        glTranslatef(-1.82, -0.9, 0.1);
        glColor3f(0., 1., 1.);
        glScalef(3.7, 1.8, 1.);
        glEnable(GL_TEXTURE_2D);
        drawSquareTex();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

int draw_menu(const TextureObject &menu, const TextureObject &play, const TextureObject &quit, int pos_x, int pos_y, bool flag_is_moving)
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glTranslatef(-10., -10., 0.1);
    glScalef(20.0, 20.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, menu.get_width(), menu.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, menu.get_image());
    glEnable(GL_TEXTURE_2D);
    drawSquareTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.5, 0., 0.);
    if (pos_x > -4.5 && pos_x < -0.5 && pos_y > -1. && pos_y < 1.)
    {
        draw_hover_button(play);
        if (flag_is_moving)
        {
            return 1;
        }
    }
    else
    {
        draw_button(play);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.5, 0., 0.);
    if (pos_x > 0.5 && pos_x < 4.5 && pos_y > -1. && pos_y < 1.)
    {
        draw_hover_button(quit);
        if (flag_is_moving)
        {
            return 2;
        }
    }
    else
    {
        draw_button(quit);
    }
    glPopMatrix();
    glPopMatrix();
    return 0;
}

int drawEndMenu(Player &player, const TextureObject &menu, const TextureObject &quit, const TextureObject &retry, const TextureObject &texture0, const TextureObject &texture1, const TextureObject &texture2, const TextureObject &texture3, const TextureObject &texture4, const TextureObject &texture5, const TextureObject &texture6, const TextureObject &texture7, const TextureObject &texture8, const TextureObject &texture9, float pos_x, float pos_y, bool flag_is_moving)
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glTranslatef(-10., -10., 0.1);
    glScalef(20.0, 20.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, menu.get_width(), menu.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, menu.get_image());
    glEnable(GL_TEXTURE_2D);
    drawSquareTex();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5, 0., 0.);
    glRotatef(-180.0, 0.0, 0.0, 1.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    player.drawScore(texture0, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.5, -3., 0.);
    if (pos_x > -4.5 && pos_x < -0.5 && pos_y >= 2. && pos_y < 4.)
    {
        draw_hover_button(retry);
        if (flag_is_moving)
        {
            player.reset();
            return 1;
        }
    }
    else
    {
        draw_button(retry);
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.5, -3., 0.);
    if (pos_x > 0.5 && pos_x < 4.5 && pos_y >= 2. && pos_y < 4.)
    {
        draw_hover_button(quit);
        if (flag_is_moving)
        {
            return 2;
        }
    }
    else
    {
        draw_button(quit);
    }
    glPopMatrix();
    glPopMatrix();
    return 3;
}