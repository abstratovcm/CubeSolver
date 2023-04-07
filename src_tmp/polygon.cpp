#include "polygon.hpp"

Polygon::Polygon() : position(glm::vec3(0.0f)),
                     rotation(0.0f),
                     scale(glm::vec2(1.0f)),
                     color(glm::vec3(0.0f)) {}

Polygon::Polygon(std::vector<glm::vec2> vertices) : position(glm::vec3(0.0f)),
                                                    rotation(0.0f),
                                                    scale(glm::vec2(1.0f)),
                                                    color(glm::vec3(0.0f)),
                                                    vertices(vertices) {}

// Setters
void Polygon::setPosition(const glm::vec3 &position) { this->position = position; }
void Polygon::setRotation(const glm::vec3 &rotation) { this->rotation = rotation; }
void Polygon::setScale(const glm::vec2 &scale) { this->scale = scale; }
void Polygon::setColor(const glm::vec3 &color) { this->color = color; }
void Polygon::setVertices(const std::vector<glm::vec2> &vertices) { this->vertices = vertices; }

// Getters
glm::vec3 Polygon::getPosition() const { return position; }
glm::vec3 Polygon::getRotation() const { return rotation; }
glm::vec2 Polygon::getScale() const { return scale; }
const glm::vec3 &Polygon::getColor() const { return color; }
const std::vector<glm::vec2> &Polygon::getVertices() const { return vertices; }
const std::size_t Polygon::getSize() const { return vertices.size(); }

// Get the model matrix
glm::mat4 Polygon::getModelMatrix() const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0f));
    return model;
}

void Polygon::updateRotation(const glm::vec3 &rotationDelta)
{
    rotation += rotationDelta;
}
