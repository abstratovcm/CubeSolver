#include "../include/initializeCube.h"

void Cube::Print()
{
    std::cout << "position: (" << position.x << ", " << position.y;
    std::cout << ", " << position.z << ")" << std::endl;
    std::cout << "rotation: (" << rotation.w << ", " << rotation.x;
    std::cout << ", " << rotation.y << ", " << rotation.z;
    std::cout << ")" << std::endl;
}

std::vector<Cube> cubes;
std::vector<Cube> originalForm;

void initializeCube(int SIZE)
{
    cubes.resize(SIZE * SIZE * SIZE);
    originalForm.resize(SIZE * SIZE * SIZE);
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            for (int z = 0; z < SIZE; z++)
            {
                int index = x * SIZE * SIZE + y * SIZE + z;
                originalForm[index].position = glm::vec3(x - (SIZE - 1) / 2.0f, y - (SIZE - 1) / 2.0f, z - (SIZE - 1) / 2.0f);
                cubes[index].position = originalForm[index].position;
            }
        }
    }
}