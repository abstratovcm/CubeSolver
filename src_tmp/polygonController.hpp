#pragma once

#include "polygonRenderer.hpp"
#include "polygon.hpp"
#include "polygonRepository.hpp"
#include "renderData.hpp"
#include <vector>
#include <memory>

class PolygonController
{
public:
    PolygonController();
    ~PolygonController();

    void run();

private:
    GLFWwindow *window;
    PolygonRenderer renderer;
    PolygonRepository repository;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void handleKeyPress(int key);
    void addRegularPolygon(unsigned int numVertices, float radius, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &color);
};