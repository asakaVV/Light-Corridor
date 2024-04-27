#pragma once

#define _USE_MATH_DEFINES
#include "../third_party/glfw/include/GLFW/glfw3.h"
#include <OpenGL/gl.h>
#include <iostream>
#include <cmath>

#define NB_SEG_CIRCLE 64

/* Camera parameters and functions */
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 100.f;
extern float theta;     // Angle between x axis and viewpoint
extern float phy;       // Angle between z axis and viewpoint
extern float dist_zoom; // Distance between origin and viewpoint

void setCamera();
void setPerspective(float fovy, float a_ratio, float z_near, float z_far);

/* Draw cannonic objet functions */
void drawSquare();

void drawCircle();

void drawCircleFilaire();

void drawCone();

void drawSphere();

/* Small tools */
float toRad(float deg);
