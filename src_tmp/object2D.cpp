#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object2D {
public:
    Object2D() : position(glm::vec3(0.0f)), rotation(0.0f), scale(glm::vec2(1.0f)) {}
    virtual ~Object2D() = default;

    // Abstract function to calculate the area of the 2D object
    virtual float getArea() const = 0;

    // Setters
    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setRotation(float rot) { rotation = rot; }
    void setScale(const glm::vec2 &scl) { scale = scl; }

    // Getters
    glm::vec3 getPosition() const { return position; }
    float getRotation() const { return rotation; }
    glm::vec2 getScale() const { return scale; }

    // Get the model matrix
    glm::mat4 getModelMatrix() const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(scale, 1.0f));
        return model;
    }

protected:
    glm::vec3 position;
    float rotation;
    glm::vec2 scale;
};
