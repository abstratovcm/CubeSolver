#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <fstream>
#include <sstream>

class PolygonRenderer
{
public:
    PolygonRenderer();
    ~PolygonRenderer();

    void init();
    void renderPolygon(const glm::vec3 &color,
                       const glm::mat4 &modelMatrix,
                       const std::vector<glm::vec2> &vertices);
    void renderRay(const glm::vec3 &startPoint, const glm::vec3 &endPoint);
    void cleanup();
    GLuint loadShader(const GLenum &shaderType, const std::string &filePath);
    void createShaderProgram(GLuint &shaderProgram,
                     const std::string &vertexPath,
                     const std::string &fragmentPath);
    void renderPlane(const glm::vec3 &planePoint, const glm::vec3 &planeNormal);

private:
    GLuint vao;
    GLuint vbo;
    GLuint polygonShaderProgram;
    GLuint rayShaderProgram;
    GLuint planeShaderProgram;
};
