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

void draw_button()
{
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-2., -1., 0);
    glVertex3f(-2., 1., 0);
    glVertex3f(2., 1., 0);
    glVertex3f(2., -1., 0);
    glEnd();
    glPushMatrix();
    {
        glTranslatef(0., 0., 0.1);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glVertex3f(-1.80, -0.80, 0);
        glVertex3f(-1.80, 0.80, 0);
        glVertex3f(1.80, 0.80, 0);
        glVertex3f(1.80, -0.80, 0);
        glEnd();
    }
    glPopMatrix();
}

void draw_hover_button()
{
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-2., -1., 0);
    glVertex3f(-2., 1., 0);
    glVertex3f(2., 1., 0);
    glVertex3f(2., -1., 0);
    glEnd();
    glPushMatrix();
    {
        glTranslatef(0., 0., 0.1);
        glBegin(GL_POLYGON);
        glColor3f(0.8, 1, 1);
        glVertex3f(-1.80, -0.80, 0);
        glVertex3f(-1.80, 0.80, 0);
        glVertex3f(1.80, 0.80, 0);
        glVertex3f(1.80, -0.80, 0);
        glEnd();
    }
    glPopMatrix();
}