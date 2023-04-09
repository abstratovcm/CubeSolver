#include "polygonController.hpp"

PolygonController::PolygonController() : window(nullptr), renderer()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW" << std::endl;
        exit(1);
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "Regular Polygon Renderer", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set key callback
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowUserPointer(window, this); // Store 'this' pointer for use in the static keyCallback

    // Add initial polygons
    makeRubiksCube(1.f);
}

PolygonController::~PolygonController()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void PolygonController::run()
{
    renderer.init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::vec3 rotation = glm::vec3(50.0f, 30.0f, 10.0f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 rayOrigin(-100.0f, 0.0f, 0.0f);
        glm::vec3 rayDirection(100.0f, 0.0f, 0.0f);
        renderer.renderRay(rayOrigin, rayDirection);

        // Define a point on the plane and its normal
        glm::vec3 planePoint(0.0f, 0.0f, 0.0f);
        glm::vec3 planeNormal(1.0f, 0.0f, 1.0f);

        // Render all the regular polygons
        for (size_t i = 0; i < repository.getSize(); i++)
        {
            repository.UpdateRotationByIndex(i, rotation, deltaTime);
            RenderData data = repository.getRenderData(i);
            float t;
            if (PolygonIntersector::intersectsRay(rayOrigin,
                                                  rayDirection,
                                                  data.modelMatrix,
                                                  data.vertices))
            {
                data.color = glm::vec3(1.0f);
            }
            if (PolygonIntersector::intersectsPlane(planePoint,
                                                    planeNormal,
                                                    data.modelMatrix,
                                                    data.vertices))
            {
                data.color = glm::vec3(0.0f);
            }
            renderer.renderPolygon(data.color, data.modelMatrix, data.vertices);
        }

        // Render the semi-transparent plane
        renderer.renderPlane(planePoint, planeNormal);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    renderer.cleanup();
}

void PolygonController::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        PolygonController *controller = static_cast<PolygonController *>(glfwGetWindowUserPointer(window));
        controller->handleKeyPress(key);
    }
}

void PolygonController::handleKeyPress(int key)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_A)
    {
        unsigned int numVertices = 3 + rand() % 8;
        float radius = 0.5f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.5f - 0.5f)));
        glm::vec3 position = glm::vec3(-2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f)), -2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f)), -2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f)));
        glm::vec3 rotation = glm::vec3(static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360.0f)), static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360.0f)), static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360.0f)));
        glm::vec3 color = glm::vec3(static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        addRegularPolygon(numVertices, radius, position, rotation, color);
    }
}

void PolygonController::addRegularPolygon(unsigned int numVertices, float radius, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &color)
{
    repository.addRegularPolygon(numVertices, radius, position, rotation, color);
}

void PolygonController::makeRubiksCube(float cubeSize)
{
    float faceSize = cubeSize / 3.0f;
    float halfCubeSize = cubeSize / 2.0f;
    float halfFaceSize = faceSize / 2.0f;
    glm::vec3 color;

    for (int face = 0; face < 6; ++face)
    {
        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                glm::vec3 position;
                glm::vec3 rotation;

                switch (face)
                {
                case 0: // Front
                    position = glm::vec3(col * faceSize - halfCubeSize + halfFaceSize,
                                         row * faceSize - halfCubeSize + halfFaceSize,
                                         halfCubeSize - halfFaceSize);
                    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
                    color = glm::vec3(1.0f, 0.0f, 0.0f); // Red
                    break;
                case 1: // Back
                    position = glm::vec3(halfCubeSize - halfFaceSize - col * faceSize,
                                         row * faceSize - halfCubeSize + halfFaceSize,
                                         -halfCubeSize + halfFaceSize);
                    rotation = glm::vec3(0.0f, 180.0f, 0.0f);
                    color = glm::vec3(0.0f, 1.0f, 0.0f); // Green
                    break;
                case 2: // Left
                    position = glm::vec3(-halfCubeSize + halfFaceSize,
                                         row * faceSize - halfCubeSize + halfFaceSize,
                                         col * faceSize - halfCubeSize + halfFaceSize);
                    rotation = glm::vec3(0.0f, 90.0f, 0.0f);
                    color = glm::vec3(0.0f, 0.0f, 1.0f); // Blue
                    break;
                case 3: // Right
                    position = glm::vec3(halfCubeSize - halfFaceSize,
                                         row * faceSize - halfCubeSize + halfFaceSize,
                                         halfCubeSize - halfFaceSize - col * faceSize);
                    rotation = glm::vec3(0.0f, -90.0f, 0.0f);
                    color = glm::vec3(1.0f, 1.0f, 0.0f); // Yellow
                    break;
                case 4: // Top
                    position = glm::vec3(col * faceSize - halfCubeSize + halfFaceSize,
                                         halfCubeSize - halfFaceSize,
                                         row * faceSize - halfCubeSize + halfFaceSize);
                    rotation = glm::vec3(90.0f, 0.0f, 0.0f);
                    color = glm::vec3(1.0f, 0.5f, 0.0f); // Orange
                    break;
                case 5: // Bottom
                    position = glm::vec3(col * faceSize - halfCubeSize + halfFaceSize,
                                         -halfCubeSize + halfFaceSize,
                                         -row * faceSize + halfCubeSize - halfFaceSize);
                    rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
                    color = glm::vec3(1.0f, 1.0f, 1.0f); // White
                    break;
                }

                repository.addRegularPolygon(4, halfFaceSize, position, rotation, color);
            }
        }
    }
}
