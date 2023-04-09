#include "polygonRepository.hpp"

PolygonRepository::PolygonRepository() = default;

// Add a regular polygon to the repository
void PolygonRepository::addRegularPolygon(const unsigned int &numVertices,
                                          const float &radius,
                                          const glm::vec3 &position,
                                          const glm::vec3 &rotation,
                                          const glm::vec3 &color)
{
    std::vector<glm::vec2> vertices;
    float angle = 2 * glm::pi<float>() / numVertices;
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        vertices.push_back(radius * glm::vec2(cos(i * angle), sin(i * angle)));
    }
    auto polygon = std::make_unique<Polygon>(vertices);
    polygon->setPosition(position);
    polygon->setRotation(rotation);
    polygon->setColor(color);
    polygons.push_back(std::move(polygon));
}

// Remove a polygon from the repository by index
void PolygonRepository::removePolygon(const std::size_t &index)
{
    if (index < polygons.size())
    {
        polygons.erase(polygons.begin() + index);
    }
}

// Get a polygon by index
Polygon *PolygonRepository::getPolygon(const std::size_t &index) const
{
    if (index < polygons.size())
    {
        return polygons[index].get();
    }
    return nullptr;
}

// Get the number of polygons in the repository
std::size_t PolygonRepository::getSize() const
{
    return polygons.size();
}

// Clear the repository
void PolygonRepository::clear()
{
    polygons.clear();
}

RenderData PolygonRepository::getRenderData(const size_t &index) const
{
    auto &polygon = polygons[index];
    RenderData data;
    data.modelMatrix = polygon->getModelMatrix();
    data.color = polygon->getColor();
    data.vertices = polygon->getVertices();
    return data;
}

void PolygonRepository::UpdateRotationByIndex(const size_t &index,
                                              const glm::vec3 &rotation,
                                              const float &deltaTime)
{
    auto &polygon = polygons[index];
    polygon->updateRotation(rotation * deltaTime);
}
