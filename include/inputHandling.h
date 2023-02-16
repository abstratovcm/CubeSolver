#ifndef INPUTHANDLING_H
#define INPUTHANDLING_H

#include <GL/glut.h>
#include <iostream>

#include "gameLogic.h"
#include "sharedVariables.h"

void normalKeys(unsigned char key, int x, int y);

void specialKeys(int key, int x, int y);

void mouse(int button, int state, int x, int y);

void motion(int x, int y);

void passiveMotion(int x, int y);

#endif