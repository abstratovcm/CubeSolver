#include "polygonRenderer.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

PolygonRenderer::PolygonRenderer() : vao(0), vbo(0), rayShaderProgram(0), planeShaderProgram(0), polygonShaderProgram(0) {}

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

    createShaderProgram(polygonShaderProgram,
                        "./src_tmp/polygonVertexShader.glsl",
                        "./src_tmp/polygonFragmentShader.glsl");

    createShaderProgram(rayShaderProgram,
                        "./src_tmp/rayVertexShader.glsl",
                        "./src_tmp/rayFragmentShader.glsl");

    createShaderProgram(planeShaderProgram,
                        "./src_tmp/planeVertexShader.glsl",
                        "./src_tmp/planeFragmentShader.glsl");
}

void PolygonRenderer::renderPolygon(const glm::vec3 &color,
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
    glUseProgram(polygonShaderProgram);

    // Set the uniforms (model, view, and projection matrices)
    GLuint modelLoc = glGetUniformLocation(polygonShaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(polygonShaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(polygonShaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Set the color uniform
    GLuint colorLoc = glGetUniformLocation(polygonShaderProgram, "color");
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

void PolygonRenderer::renderRay(const glm::vec3 &startPoint, const glm::vec3 &endPoint)
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
    glUseProgram(rayShaderProgram);

    // Set the view and projection matrix uniforms
    GLuint viewLoc = glGetUniformLocation(rayShaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(rayShaderProgram, "projection");
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

void PolygonRenderer::renderPlane(const glm::vec3 &planePoint, const glm::vec3 &planeNormal)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create a local coordinate system on the plane
    glm::vec3 planeUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 planeRight;
    if (glm::length(glm::cross(planeNormal, planeUp)) < 1e-6)
    {
        planeUp = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    planeRight = glm::normalize(glm::cross(planeNormal, planeUp));
    planeUp = glm::normalize(glm::cross(planeRight, planeNormal));

    // Create plane vertices
    GLfloat planeVertices[] = {
        // positions
        planePoint.x - 0.5f * planeRight.x - 0.5f * planeUp.x,
        planePoint.y - 0.5f * planeRight.y - 0.5f * planeUp.y,
        planePoint.z - 0.5f * planeRight.z - 0.5f * planeUp.z,

        planePoint.x + 0.5f * planeRight.x - 0.5f * planeUp.x,
        planePoint.y + 0.5f * planeRight.y - 0.5f * planeUp.y,
        planePoint.z + 0.5f * planeRight.z - 0.5f * planeUp.z,

        planePoint.x + 0.5f * planeRight.x + 0.5f * planeUp.x,
        planePoint.y + 0.5f * planeRight.y + 0.5f * planeUp.y,
        planePoint.z + 0.5f * planeRight.z + 0.5f * planeUp.z,

        planePoint.x - 0.5f * planeRight.x + 0.5f * planeUp.x,
        planePoint.y - 0.5f * planeRight.y + 0.5f * planeUp.y,
        planePoint.z - 0.5f * planeRight.z + 0.5f * planeUp.z};

    // Plane indices
    GLuint planeIndices[] = {
        0, 1, 2,
        2, 3, 0};

    // Create VAO and VBO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    // Bind and set element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);

    // Use shader program
    glUseProgram(planeShaderProgram);

    // Set the plane color (RGBA)
    glm::vec4 planeColor(1.0f, 1.0f, 1.0f, 0.5f); // Semi-transparent white
    GLint planeColorLoc = glGetUniformLocation(planeShaderProgram, "planeColor");
    glUniform4fv(planeColorLoc, 1, glm::value_ptr(planeColor));

    // Set model, view, and projection matrices
    // (assuming you have model, view, and projection matrices already set up)
    GLint modelLoc = glGetUniformLocation(planeShaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(planeShaderProgram, "view");
    GLint projLoc = glGetUniformLocation(planeShaderProgram, "projection");
    // Set the model matrix

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); // Scale the plane
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Render the semi-transparent plane
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Disable blending after rendering the semi-transparent object
    glDisable(GL_BLEND);
}

void PolygonRenderer::cleanup()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(polygonShaderProgram);
    glDeleteProgram(rayShaderProgram);
    glDeleteProgram(planeShaderProgram);
}

GLuint PolygonRenderer::loadShader(const GLenum &shaderType, const std::string &filePath)
{
    // Read shader file
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return 0;
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    std::string shaderSource = shaderStream.str();

    // Compile shader
    const char *shaderSourceCStr = shaderSource.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourceCStr, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        return 0;
    }

    return shader;
}

void PolygonRenderer::createShaderProgram(GLuint &shaderProgram,
                                          const std::string &vertexPath,
                                          const std::string &fragmentPath)
{
    // Load and compile shaders
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexPath);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentPath);

    // Create and link the shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }

    // Delete the shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
