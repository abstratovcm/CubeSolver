#ifndef SHAREDVARIABLES_H
#define SHAREDVARIABLES_H

#include <functional>
#include <GL/glut.h>
#include <string>

#include "initializeCube.h"

extern int SIDES;
extern double EPSILON;
extern double cubeSize;
extern const int FRONT;
extern const int BACK;
extern const int LEFT;
extern const int RIGHT;
extern const int TOP;
extern const int BOTTOM;

// Initialize variables for camera position and orientation
extern GLfloat cameraX;
extern GLfloat cameraY;
extern GLfloat cameraZ;
extern GLfloat cameraYaw;
extern GLfloat cameraPitch;
extern GLfloat cameraRow;

extern std::string text;

// Initialize variables for mouse movement
extern int lastMouseX;
extern int lastMouseY;
extern bool mouseDown;

#endif