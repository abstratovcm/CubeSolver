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

    void addRegularPolygon(const unsigned int &numVertices,
                           const float &radius,
                           const glm::vec3 &position,
                           const glm::vec3 &rotation,
                           const glm::vec3 &color);
    void removePolygon(const std::size_t &index);
    Polygon *getPolygon(const std::size_t &index) const;
    float getTotalArea() const;
    std::size_t getSize() const;
    void clear();
    RenderData getRenderData(const size_t &index) const;
    void UpdateRotationByIndex(const size_t &index,
                               const glm::vec3 &rotation,
                               const float &deltaTime);

private:
    std::vector<std::unique_ptr<Polygon>> polygons;
};
