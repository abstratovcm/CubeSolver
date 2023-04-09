#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

class PolygonIntersector
{
public:
    static bool intersectsRay(const glm::vec3 &rayOrigin,
                              const glm::vec3 &rayDirection,
                              const glm::mat4 &modelMatrix,
                              const std::vector<glm::vec2> &vertices);
    static bool intersectsPlane(const glm::vec3 &planePoint,
                                const glm::vec3 &planeNormal,
                                const glm::mat4 &modelMatrix,
                                const std::vector<glm::vec2> &vertices);
    static glm::vec3 getVertex3DPosition(const glm::mat4 &modelMatrix,
                                         const glm::vec2 &originalVertex);
};
