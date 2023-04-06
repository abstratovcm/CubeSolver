#include "regularPolygonController.hpp"

RegularPolygonController::RegularPolygonController() : window(nullptr), renderer(), polygon(6, 1.0f) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW" << std::endl;
        exit(1);
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "Regular Polygon Renderer", NULL, NULL);
    if (!window) {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set key callback
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowUserPointer(window, this); // Store 'this' pointer for use in the static keyCallback

}

RegularPolygonController::~RegularPolygonController() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void RegularPolygonController::run() {
    renderer.init();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
                // Clear the screen
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the regular polygon
        renderer.render(polygon);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    renderer.cleanup();
}

void RegularPolygonController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        RegularPolygonController* controller = static_cast<RegularPolygonController*>(glfwGetWindowUserPointer(window));
        controller->handleKeyPress(key);
    }
}

void RegularPolygonController::handleKeyPress(int key) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (key == GLFW_KEY_UP) {
        polygon.setNumVertices(polygon.getNumVertices() + 1);
    } else if (key == GLFW_KEY_DOWN) {
        if (polygon.getNumVertices() > 3) {
            polygon.setNumVertices(polygon.getNumVertices() - 1);
        }
    }
}

