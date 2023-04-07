#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "renderData.hpp"

class PolygonRenderer
{
public:
    PolygonRenderer();
    ~PolygonRenderer();

    void init();
    void render(const RenderData data);
    void cleanup();

private:
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
};
