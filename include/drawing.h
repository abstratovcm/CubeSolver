#ifndef DRAWING_H
#define DRAWING_H

#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glut.h>

#include "initializeCube.h"
#include "sharedVariables.h"

void personalizedGlutCube(GLdouble width);

void drawCube(const Cube &cube);

void drawCubes();

void drawText();

void updateCamera();

#endif