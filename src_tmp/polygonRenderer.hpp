#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class PolygonRenderer
{
public:
    PolygonRenderer();
    ~PolygonRenderer();

    void init();
    void render(const std::vector<glm::vec2> &vertices,
                const glm::mat4 &modelMatrix,
                const glm::vec3 &color);
    void cleanup();

private:
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
};
