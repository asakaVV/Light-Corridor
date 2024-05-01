#pragma once

#define GL_SILENCE_DEPRECATION
#include "../third_party/glfw/include/GLFW/glfw3.h"
#include <OpenGL/gl.h>
#include "3D_tools.hpp"

class Drawable
{
public:
    virtual void draw() const = 0;
};
