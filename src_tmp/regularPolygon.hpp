#pragma once

#include "polygon.hpp"

class RegularPolygon : public Polygon
{
public:
    RegularPolygon(unsigned int numVertices_, float radius);

    float getArea() const override;

    // Setters
    void setNumVertices(unsigned int vertices);
    void setRadius(float r);

    // Getters
    unsigned int getNumVertices() const;
    float getRadius() const;

private:
    unsigned int numVertices;
    float radius;
};