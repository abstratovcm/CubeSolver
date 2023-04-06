#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "regularPolygon.cpp"

class RegularPolygonRenderer {
public:
    RegularPolygonRenderer();
    ~RegularPolygonRenderer();

    void init();
    void render(const RegularPolygon& polygon);
    void cleanup();

private:
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
};
