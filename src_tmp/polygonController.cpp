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
    addPolygon(3, 1.0f, glm::vec3(-1.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    addPolygon(6, 1.0f, glm::vec3(1.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
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

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render all the regular polygons
        for (auto &polygon : polygons)
        {
            polygon->updateRotation(glm::vec3(50.0f, 30.0f, 10.0f) * deltaTime);
            std::vector<glm::vec2> vertices = polygon->getVertices();
            glm::mat4 modelMatrix = polygon->getModelMatrix();
            glm::vec3 color = polygon->getColor();
            renderer.render(vertices, modelMatrix, color);
        }

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
        addPolygon(numVertices, radius, position, rotation, color);
    }
}

void PolygonController::addPolygon(unsigned int numVertices, float radius, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &color)
{
    polygons.emplace_back(std::make_unique<RegularPolygon>(numVertices, radius));
    std::unique_ptr<Polygon>& polygon = polygons.back();
    polygon->setPosition(position);
    polygon->setRotation(rotation);
    polygon->setColor(color);
}