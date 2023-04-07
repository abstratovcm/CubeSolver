#pragma once

#include <vector>
#include <memory>

#include "polygon.hpp"

class PolygonRepository {
public:
    PolygonRepository();
    virtual ~PolygonRepository() = default;

    void addPolygon(std::unique_ptr<Polygon> polygon);
    void removePolygon(std::size_t index);
    Polygon* getPolygon(std::size_t index) const;
    float getTotalArea() const;
    std::size_t getSize() const;
    void clear();

private:
    std::vector<std::unique_ptr<Polygon>> polygons;
};
