#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Polygon
{
public:
    Polygon() : position(glm::vec3(0.0f)), rotation(0.0f), scale(glm::vec2(1.0f)) {}
    virtual ~Polygon() = default;

    // Abstract function to calculate the area of the 2D object
    virtual float getArea() const = 0;

    // Setters
    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setRotation(const glm::vec3 &rot) { rotation = rot; }
    void setScale(const glm::vec2 &scl) { scale = scl; }
    void setColor(const glm::vec3 &col) { color = col; }
    void setVertices(const std::vector<glm::vec2> &ver) { vertices = ver; }

    // Getters
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    glm::vec2 getScale() const { return scale; }
    const glm::vec3 &getColor() const { return color; }
    const std::vector<glm::vec2> &getVertices() const { return vertices; }

    // Get the model matrix
    glm::mat4 getModelMatrix() const
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(scale, 1.0f));
        return model;
    }

    void updateRotation(const glm::vec3 &rotationDelta)
    {
        rotation += rotationDelta;
    }

protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec2 scale;
    glm::vec3 color;
    std::vector<glm::vec2> vertices;
};
