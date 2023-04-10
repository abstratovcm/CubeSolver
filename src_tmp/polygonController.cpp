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
        // renderer.renderRay(rayOrigin, rayDirection);

        // Define a point on the plane and its normal
        glm::vec3 planePoint1(0.0f, 0.0f, 0.0f);
        glm::vec3 planeNormal1(1.0f, 0.0f, 1.0f);
        glm::vec3 planePoint2(-0.5f, 0.0f, -0.5f);
        glm::vec3 planeNormal2(1.0f, 0.0f, 1.0f);

        // Render all the regular polygons
        for (size_t i = 0; i < repository.getSize(); i++)
        {
            // repository.UpdateRotationByIndex(i, rotation, deltaTime);
            RenderData data = repository.getRenderData(i);
            float t;
            // if (PolygonIntersector::intersectsRay(rayOrigin,
            //                                       rayDirection,
            //                                       data.modelMatrix,
            //                                       data.vertices))
            //{
            //     data.color = glm::vec3(1.0f);
            // }
            // if (PolygonIntersector::isBetweenPlanes(data.modelMatrix,
            //                                         data.vertices,
            //                                         planePoint1,
            //                                         planeNormal1,
            //                                         planePoint2,
            //                                         planeNormal2))
            //{
            //     data.color = glm::vec3(0.0f);
            // }
            renderer.renderPolygon(data.color, data.modelMatrix, data.vertices);
        }

        // Render the semi-transparent plane
        // renderer.renderPlane(planePoint2, planeNormal2);
        // renderer.renderPlane(planePoint1, planeNormal1);

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

void PolygonController::makeRubiksCube(float sideLength)
{

    // Define the colors of a Rubik's Cube
    std::vector<glm::vec3> colors = {
        glm::vec3(1.0f, 0.0f, 0.0f),  // Red
        glm::vec3(0.5f, 0.0f, 0.0f),  // Red
        glm::vec3(0.0f, 1.0f, 0.0f),  // Green
        glm::vec3(0.0f, 0.5f, 0.0f),  // Green
        glm::vec3(0.0f, 0.0f, 1.0f),  // Blue
        glm::vec3(0.0f, 0.0f, 0.5f),  // Blue
        glm::vec3(1.0f, 1.0f, 0.0f),  // Yellow
        glm::vec3(0.5f, 0.5f, 0.0f),  // Yellow
        glm::vec3(1.0f, 0.5f, 0.0f),  // Orange
        glm::vec3(0.5f, 0.25f, 0.0f), // Orange
        glm::vec3(1.0f, 1.0f, 1.0f),  // White
        glm::vec3(0.5f, 0.5f, 0.5f)   // White
    };
    float cubeSize = .5f;
    float sideOffset = 2 * cubeSize;
    glm::vec3 position;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            position = glm::vec3(2 * j * cubeSize - sideOffset, 2 * i * cubeSize - sideOffset, .0f);
            addRegularPolygon(4, cubeSize * sqrt(2), position, glm::vec3(0.0f, 0.0f, 45.0f), colors[(i + j) % 2]);
            position = glm::vec3(2 * j * cubeSize - sideOffset, 2 * i * cubeSize - sideOffset, -6 * cubeSize);
            addRegularPolygon(4, cubeSize * sqrt(2), position, glm::vec3(0.0f, 0.0f, 45.0f), colors[2 +(i + j) % 2]);
            position = glm::vec3(3 * cubeSize, 2 * i * cubeSize - sideOffset, 2 * j * cubeSize - sideOffset - 3 * cubeSize);
            addRegularPolygon(4, cubeSize * sqrt(2), position, glm::vec3(0.0f, 90.0f, 45.0f), colors[4 + (i + j) % 2]);
            position = glm::vec3(-3 * cubeSize, 2 * i * cubeSize - sideOffset, 2 * j * cubeSize - sideOffset - 3 * cubeSize);
            addRegularPolygon(4, cubeSize * sqrt(2), position, glm::vec3(0.0f, 90.0f, 45.0f), colors[6 + (i + j) % 2]);
            position = glm::vec3(2 * i * cubeSize - sideOffset, -3 * cubeSize, 2 * j * cubeSize - sideOffset - 3 * cubeSize);
            addRegularPolygon(4, cubeSize * sqrt(2), position, glm::vec3(90.0f, 0.0f, 45.0f), colors[8 + (i + j) % 2]);
            position = glm::vec3(2 * i * cubeSize - sideOffset, 3 * cubeSize, 2 * j * cubeSize - sideOffset - 3 * cubeSize);
            addRegularPolygon(4, cubeSize * sqrt(2), position, glm::vec3(90.0f, 0.0f, 45.0f), colors[10 + (i + j) % 2]);
        }
    }
}
