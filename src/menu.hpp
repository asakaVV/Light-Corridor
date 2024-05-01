#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "3D_tools.hpp"
#include "texture.hpp"

void draw_scene();

void draw_button(const TextureObject &texture);

void draw_hover_button(const TextureObject &texture);

int draw_menu(const TextureObject &menu, const TextureObject &play, const TextureObject &quit, int pos_x, int pos_y, bool flag_is_moving);