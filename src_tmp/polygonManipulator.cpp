#include "polygonManipulator.hpp"

bool PolygonIntersector::intersectsRay(const glm::vec3 &rayOrigin,
                                       const glm::vec3 &rayDirection,
                                       const glm::mat4 &modelMatrix,
                                       const std::vector<glm::vec2> &vertices)
{
    constexpr float EPSILON = 1e-6f;

    // Get the 3D position of the polygon's center
    glm::vec3 center = glm::vec3(modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        float t;

        // Get the 3D positions of the current vertex and the next vertex
        glm::vec3 v0 = getVertex3DPosition(modelMatrix, vertices[i]);
        glm::vec3 v1 = getVertex3DPosition(modelMatrix, vertices[(i + 1) % vertices.size()]);

        // Create a triangle composed of the center, v0, and v1
        glm::vec3 edge1 = v1 - center;
        glm::vec3 edge2 = v0 - center;

        // Perform the ray-triangle intersection test
        glm::vec3 pvec = glm::cross(rayDirection, edge2);
        float det = glm::dot(edge1, pvec);

        if (std::abs(det) < EPSILON)
        {
            continue;
        }

        float inv_det = 1.0f / det;
        glm::vec3 tvec = rayOrigin - center;
        float u = glm::dot(tvec, pvec) * inv_det;

        if (u < 0.0f || u > 1.0f)
        {
            continue;
        }

        glm::vec3 qvec = glm::cross(tvec, edge1);
        float v = glm::dot(rayDirection, qvec) * inv_det;

        if (v < 0.0f || u + v > 1.0f)
        {
            continue;
        }

        t = glm::dot(edge2, qvec) * inv_det;
        return true;
    }

    return false;
}

bool PolygonIntersector::intersectsPlane(const glm::vec3 &planePoint,
                                         const glm::vec3 &planeNormal,
                                         const glm::mat4 &modelMatrix,
                                         const std::vector<glm::vec2> &vertices)
{

    // Calculate the signed distance from the plane to the first vertex
    float prevDist = glm::dot(getVertex3DPosition(modelMatrix, vertices[0]) - planePoint, planeNormal);

    for (size_t i = 1; i < vertices.size(); ++i)
    {
        // Calculate the signed distance from the plane to the current vertex
        float currentDist = glm::dot(getVertex3DPosition(modelMatrix, vertices[i]) - planePoint, planeNormal);

        // Check if the signs of the distances are different
        if (prevDist * currentDist < 0)
        {
            return true; // The polygon intersects the plane
        }

        prevDist = currentDist;
    }

    return false; // The polygon does not intersect the plane
}

bool PolygonIntersector::isBetweenPlanes(const glm::mat4 &modelMatrix,
                                         const std::vector<glm::vec2> &vertices,
                                         const glm::vec3 &planePoint1,
                                         const glm::vec3 &planeNormal1,
                                         const glm::vec3 &planePoint2,
                                         const glm::vec3 &planeNormal2)
{
    int abovePlane1 = 0;
    int belowPlane1 = 0;
    int abovePlane2 = 0;
    int belowPlane2 = 0;

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        glm::vec3 v = getVertex3DPosition(modelMatrix, vertices[i]);
        float distanceToPlane1 = glm::dot(v - planePoint1, planeNormal1);
        float distanceToPlane2 = glm::dot(v - planePoint2, planeNormal2);

        if (distanceToPlane1 > 0.0f)
        {
            abovePlane1++;
        }
        else if (distanceToPlane1 < 0.0f)
        {
            belowPlane1++;
        }
        else
        {
            return true;
        }

        if (distanceToPlane2 > 0.0f)
        {
            abovePlane2++;
        }
        else if (distanceToPlane2 < 0.0f)
        {
            belowPlane2++;
        }
        else
        {
            return true;
        }
    }

    if (abovePlane1 > 0 && belowPlane1 > 0)
    {
        return true;
    }

    if (abovePlane2 > 0 && belowPlane2 > 0)
    {
        return true;
    }

    if ((abovePlane1 > 0 && belowPlane2 > 0) || (abovePlane2 > 0 && belowPlane1 > 0))
    {
        return true;
    }

    if (abovePlane1 == 0 && abovePlane2 == 0)
    {
        return false;
    }

    if (belowPlane1 == 0 && belowPlane2 == 0)
    {
        return false;
    }

    return true;
}

glm::vec3 PolygonIntersector::getVertex3DPosition(const glm::mat4 &modelMatrix, const glm::vec2 &originalVertex)
{
    glm::vec4 vertex4D(originalVertex, 0.0f, 1.0f);
    glm::vec4 transformedVertex4D = modelMatrix * vertex4D;
    return glm::vec3(transformedVertex4D);
}
