#include "../include/sharedVariables.h"

int SIDES = 6;
double EPSILON = 0.3;
double cubeSize = 1;
const int FRONT = 0;
const int BACK = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int TOP = 4;
const int BOTTOM = 5;


// Initialize variables for camera position and orientation
GLfloat cameraX = 5.0f;
GLfloat cameraY = 5.0f;
GLfloat cameraZ = 5.0f;
GLfloat cameraYaw = 0.0f;
GLfloat cameraPitch = 0.0f;
GLfloat cameraRow = 0.0f;

std::string text = "0 0";

// Initialize variables for mouse movement
int lastMouseX = 0;
int lastMouseY = 0;
bool mouseDown = false;