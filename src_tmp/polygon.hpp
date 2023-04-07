#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Polygon
{
public:
    Polygon(std::vector<glm::vec2> vertices);
    Polygon();
    virtual ~Polygon() = default;

    // Setters
    void setPosition(const glm::vec3 &position);
    void setRotation(const glm::vec3 &rotation);
    void setScale(const glm::vec2 &scale);
    void setColor(const glm::vec3 &color);
    void setVertices(const std::vector<glm::vec2> &vertices);

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec2 getScale() const;
    const glm::vec3 &getColor() const;
    const std::vector<glm::vec2> &getVertices() const;
    const std::size_t getSize() const;

    // Get the model matrix
    glm::mat4 getModelMatrix() const;

    void updateRotation(const glm::vec3 &rotationDelta);

protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec2 scale;
    glm::vec3 color;
    std::vector<glm::vec2> vertices;
};
