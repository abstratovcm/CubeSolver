#include "object2D.cpp"

class RegularPolygon : public Object2D {
public:
    RegularPolygon(unsigned int vertices, float radius) : numVertices(vertices), radius(radius) {}

    float getArea() const override {
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
