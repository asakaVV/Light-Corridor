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
#include "player.hpp"

void draw_scene();

void draw_button(const TextureObject &texture);

void draw_hover_button(const TextureObject &texture);

int draw_menu(const TextureObject &menu, const TextureObject &play, const TextureObject &quit, int pos_x, int pos_y, bool flag_is_moving);

int drawEndMenu(Player &player, const TextureObject &menu, const TextureObject &quit, const TextureObject &retry, const TextureObject &texture0, const TextureObject &texture1, const TextureObject &texture2, const TextureObject &texture3, const TextureObject &texture4, const TextureObject &texture5, const TextureObject &texture6, const TextureObject &texture7, const TextureObject &texture8, const TextureObject &texture9, float pos_x, float pos_y, bool flag_is_moving);
