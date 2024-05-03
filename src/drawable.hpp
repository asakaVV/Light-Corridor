#pragma once

#define GL_SILENCE_DEPRECATION
#include "../third_party/glfw/include/GLFW/glfw3.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "3D_tools.hpp"

class Drawable
{
public:
    virtual void draw() const = 0;
};
