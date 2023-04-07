#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct RenderData {
    glm::mat4 modelMatrix;
    glm::vec3 color;
    std::vector<glm::vec2> vertices;
};
