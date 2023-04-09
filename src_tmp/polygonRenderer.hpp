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
    void render(const glm::vec3 &color,
                const glm::mat4 &modelMatrix,
                const std::vector<glm::vec2> &vertices);
    void renderLine(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
    void cleanup();

private:
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
    GLuint lineShaderProgram;
};
