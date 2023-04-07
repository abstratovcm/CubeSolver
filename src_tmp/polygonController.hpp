#pragma once

#include "polygonRenderer.hpp"
#include "regularPolygon.cpp"
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
    std::vector<std::unique_ptr<Polygon>> polygons;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void handleKeyPress(int key);
    void addPolygon(unsigned int numVertices, float radius, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &color);
};