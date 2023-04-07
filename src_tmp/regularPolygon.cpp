#include "regularPolygon.hpp"

RegularPolygon::RegularPolygon(unsigned int numVertices_, float radius) : numVertices(numVertices_), radius(radius)
{
    float angle = 2 * glm::pi<float>() / numVertices;
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        vertices.push_back(radius * glm::vec2(cos(i * angle), sin(i * angle)));
    }
}

float RegularPolygon::getArea() const
{
    return 0.5f * numVertices * radius * radius * glm::sin(2 * glm::pi<float>() / numVertices);
}

// Setters
void RegularPolygon::setNumVertices(unsigned int vertices) { numVertices = vertices; }
void RegularPolygon::setRadius(float r) { radius = r; }

// Getters
unsigned int RegularPolygon::getNumVertices() const { return numVertices; }
float RegularPolygon::getRadius() const { return radius; }
