#include "polygonRenderer.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Define the vertex shader source
const char *vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec2 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

out vec3 fragmentColor;

void main() {
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
    fragmentColor = color;
}

)";

// Define the fragment shader source
const char *fragmentShaderSource = R"(
#version 330 core

in vec3 fragmentColor;

out vec4 color;

void main() {
    color = vec4(fragmentColor, 1.0);
}
)";

// Define the line vertex shader source
const char *lineVertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * vec4(position, 1.0);
}
)";

// Define the line fragment shader source
const char *lineFragmentShaderSource = R"(
#version 330 core

out vec4 color;

void main() {
    color = vec4(1.0, 0.0, 0.0, 1.0); // Set the line color (e.g., red)
}
)";

PolygonRenderer::PolygonRenderer() : vao(0), vbo(0), shaderProgram(0) {}

PolygonRenderer::~PolygonRenderer()
{
    cleanup();
}

void PolygonRenderer::init()
{
    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
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

    // Create and compile the line vertex shader
    GLuint lineVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(lineVertexShader, 1, &lineVertexShaderSource, NULL);
    glCompileShader(lineVertexShader);

    // Create and compile the line fragment shader
    GLuint lineFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lineFragmentShader, 1, &lineFragmentShaderSource, NULL);
    glCompileShader(lineFragmentShader);

    // Create and link the line shader program
    lineShaderProgram = glCreateProgram();
    glAttachShader(lineShaderProgram, lineVertexShader);
    glAttachShader(lineShaderProgram, lineFragmentShader);
    glLinkProgram(lineShaderProgram);

    // Delete the line shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void PolygonRenderer::render(const glm::vec3 &color,
                             const glm::mat4 &modelMatrix,
                             const std::vector<glm::vec2> &vertices)
{

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);

    // Use the shader program
    glUseProgram(shaderProgram);

    // Set the uniforms (model, view, and projection matrices)
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Set the color uniform
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));

    // Set the view and projection matrices as identity matrices for simplicity
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the regular polygon
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void PolygonRenderer::renderLine(const glm::vec3 &startPoint, const glm::vec3 &endPoint)
{
    // Create and bind the Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and bind the Vertex Buffer Object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Create an array with the start and end points of the line
    glm::vec3 lineVertices[] = {startPoint, endPoint};
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

    // Set the vertex attribute pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // Use the shader program
    glUseProgram(lineShaderProgram);

    // Set the view and projection matrix uniforms
    GLuint viewLoc = glGetUniformLocation(lineShaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(lineShaderProgram, "projection");
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the line
    glDrawArrays(GL_LINES, 0, 2);

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void PolygonRenderer::cleanup()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(lineShaderProgram);
}
