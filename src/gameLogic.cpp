#include "../include/gameLogic.h"

extern std::vector<Cube> cubes;

void Reset()
{
    for (int index = 0; index < cubes.size(); index++)
    {
        cubes[index].rotation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f));
        cubes[index].position = originalForm[index].position;
    }
}

bool IsSolved()
{

    for (int i = 0; i < cubes.size(); i++)
    {
        if (cubes[i].rotation.x != 0 || cubes[i].rotation.y != 0 || cubes[i].rotation.z != 0)
        {
            return false;
        }
    }
    return true;
}

void moveSide(int side, int direction)
{
    // Translate the side in the desired direction
    glm::vec3 translation = glm::vec3(0.0f);
    switch (side)
    {
    case 0: // Front
        translation = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    case 1: // Back
        translation = glm::vec3(0.0f, 0.0f, -1.0f);
        break;
    case 2: // Left
        translation = glm::vec3(-1.0f, 0.0f, 0.0f);
        break;
    case 3: // Right
        translation = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case 4: // Top
        translation = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case 5: // Bottom
        translation = glm::vec3(0.0f, -1.0f, 0.0f);
        break;
    default:
        break;
    }
    translation *= 0.5f * cubeSize;

    // Rotate the side 90 degrees in the desired direction
    glm::vec3 axis = glm::vec3(0.0f);
    float angle = 90.0f;
    switch (side)
    {
    case 0: // Front
    case 1: // Back
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    case 2: // Left
    case 3: // Right
        axis = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case 4: // Top
    case 5: // Bottom
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    default:
        break;
    }
    if (direction == -1)
    {
        angle = -angle;
    }
    // Apply the translation and rotation to each cube on the side
    for (int i = 0; i < cubes.size(); i++)
    {
        Cube &cube = cubes[i];

        // Check if the cube is on the correct side
        switch (side)
        {
        case 0: // Front
            if (abs(cube.position.z - (0.8f * cubeSize)) > EPSILON)
            {
                continue;
            }
            break;
        case 1: // Back
            if (abs(cube.position.z + (0.8f * cubeSize)) > EPSILON)
            {
                continue;
            }
            break;
        case 2: // Left
            if (abs(cube.position.x + (0.8f * cubeSize)) > EPSILON)
            {
                continue;
            }
            break;
        case 3: // Right
            if (abs(cube.position.x - (0.8f * cubeSize)) > EPSILON)
            {
                continue;
            }
            break;
        case 4: // Top
            if (abs(cube.position.y - (0.8f * cubeSize)) > EPSILON)
            {
                continue;
            }
            break;
        case 5: // Bottom
            if (abs(cube.position.y + (0.8f * cubeSize)) > EPSILON)
            {
                continue;
            }
            break;
        default:
            break;
        }

        // Translate and rotate the cube
        glm::quat rotation = glm::angleAxis(glm::radians(angle), axis);
        cube.position = rotation * cube.position;
        cube.rotation = rotation * cube.rotation;
    }
}