#pragma once

#include <vector>
#include <memory>

#include "polygon.hpp"
#include "renderData.hpp"

class PolygonRepository
{
public:
    PolygonRepository();
    virtual ~PolygonRepository() = default;

    void addRegularPolygon(unsigned int numVertices,
                           float radius,
                           const glm::vec3 &position,
                           const glm::vec3 &rotation,
                           const glm::vec3 &color);
    void removePolygon(std::size_t index);
    Polygon *getPolygon(std::size_t index) const;
    float getTotalArea() const;
    std::size_t getSize() const;
    void clear();
    RenderData getRenderData(size_t index) const;
    void UpdateRotationByIndex(size_t index, glm::vec3 rotation, float deltaTime);

private:
    std::vector<std::unique_ptr<Polygon>> polygons;
};
