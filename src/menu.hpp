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

void draw_scene();

void draw_button();

void draw_hover_button();