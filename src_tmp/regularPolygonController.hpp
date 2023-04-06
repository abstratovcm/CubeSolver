#pragma once

#include "regularPolygonRenderer.hpp"

class RegularPolygonController {
public:
    RegularPolygonController();
    ~RegularPolygonController();

    void run();

private:
    GLFWwindow* window;
    RegularPolygonRenderer renderer;
    RegularPolygon polygon;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleKeyPress(int key);
};
