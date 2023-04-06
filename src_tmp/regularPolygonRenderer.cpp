#include "regularPolygonRenderer.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Define the vertex shader source
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec2 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
}
)";

// Define the fragment shader source
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 fragColor;

void main() {
    fragColor = vec4(1.0, 0.5, 0.0, 1.0);
}
)";

RegularPolygonRenderer::RegularPolygonRenderer() : vao(0), vbo(0), shaderProgram(0) {}

RegularPolygonRenderer::~RegularPolygonRenderer() {
    cleanup();
}

void RegularPolygonRenderer::init() {
    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create and link the shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void RegularPolygonRenderer::render(const RegularPolygon& polygon) {
    // Generate vertex data for the regular polygon
    std::vector<glm::vec2> vertices;
    float angle = 2 * glm::pi<float>() / polygon.getNumVertices();
    for (unsigned int i = 0; i < polygon.getNumVertices(); ++i) {
        vertices.push_back(polygon.getRadius() * glm::vec2(cos(i * angle), sin(i * angle)));
    }

    // Create the Vertex Array Object and Vertex Buffer Object
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind the Vertex Array Object
    glBindVertexArray(vao);

        // Bind and fill the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Set the uniforms (model, view, and projection matrices)
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(polygon.getModelMatrix()));

    // Set the view and projection matrices as identity matrices for simplicity
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the regular polygon
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void RegularPolygonRenderer::cleanup() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
}
