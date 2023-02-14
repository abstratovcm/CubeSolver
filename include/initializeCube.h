#ifndef INITIALIZECUBE_H
#define INITIALIZECUBE_H

#include <iostream>
#include <glm/gtx/quaternion.hpp>

#include "sharedVariables.h"

struct Cube
{
    glm::vec3 position;
    glm::quat rotation;
    void Print();
};

extern std::vector<Cube> cubes;
extern std::vector<Cube> originalForm;

void initializeCube(int SIZE);

#endif