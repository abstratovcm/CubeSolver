#include "polygon.cpp"

class RegularPolygon : public Polygon
{
public:
    RegularPolygon(unsigned int numVertices_, float radius) : numVertices(numVertices_), radius(radius)
    {
        float angle = 2 * glm::pi<float>() / numVertices;
        for (unsigned int i = 0; i < numVertices; ++i)
        {
            vertices.push_back(radius * glm::vec2(cos(i * angle), sin(i * angle)));
        }
    }

    float getArea() const override
    {
        return 0.5f * numVertices * radius * radius * glm::sin(2 * glm::pi<float>() / numVertices);
    }

    // Setters
    void setNumVertices(unsigned int vertices) { numVertices = vertices; }
    void setRadius(float r) { radius = r; }

    // Getters
    unsigned int getNumVertices() const { return numVertices; }
    float getRadius() const { return radius; }

private:
    unsigned int numVertices;
    float radius;
};
