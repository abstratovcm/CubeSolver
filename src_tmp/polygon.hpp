#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Polygon
{
public:
    Polygon();
    virtual ~Polygon() = default;

    // Abstract function to calculate the area of the 2D object
    virtual float getArea() const = 0;

    // Setters
    void setPosition(const glm::vec3 &pos);
    void setRotation(const glm::vec3 &rot);
    void setScale(const glm::vec2 &scl);
    void setColor(const glm::vec3 &col);
    void setVertices(const std::vector<glm::vec2> &ver);

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec2 getScale() const;
    const glm::vec3 &getColor() const;
    const std::vector<glm::vec2> &getVertices() const;

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
