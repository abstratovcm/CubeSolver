#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include <glm/gtx/quaternion.hpp>

#include "sharedVariables.h"
#include "initializeCube.h"

void moveSide(int side, int direction);

bool IsSolved();

void Reset();

#endif