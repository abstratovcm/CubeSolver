#include "polygonRepository.hpp"

PolygonRepository::PolygonRepository() = default;

// Add a polygon to the repository
void PolygonRepository::addPolygon(std::unique_ptr<Polygon> polygon)
{
    polygons.push_back(std::move(polygon));
}

// Remove a polygon from the repository by index
void PolygonRepository::removePolygon(std::size_t index)
{
    if (index < polygons.size())
    {
        polygons.erase(polygons.begin() + index);
    }
}

// Get a polygon by index
Polygon *PolygonRepository::getPolygon(std::size_t index) const
{
    if (index < polygons.size())
    {
        return polygons[index].get();
    }
    return nullptr;
}

// Get the total area of all polygons in the repository
float PolygonRepository::getTotalArea() const
{
    float totalArea = 0.0f;
    for (const auto &polygon : polygons)
    {
        totalArea += polygon->getArea();
    }
    return totalArea;
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
