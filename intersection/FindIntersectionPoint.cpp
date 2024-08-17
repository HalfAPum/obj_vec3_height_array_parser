//
// Created by o.narvatov on 8/17/2024.
//

#include "FindIntersectionPoint.h"

#include <cmath>

double FindIntersectionPoint::dotProduct(const Point3D &v1, const Point3D &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Point3D FindIntersectionPoint::crossProduct(const Point3D &v1, const Point3D &v2) {
    Point3D result{};
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

inline double length(const Point3D& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

bool FindIntersectionPoint::isPointInTriangle(const Point3D &p) const {
    // Check if point is on the plane
    if (abs(dotProduct(normal, p - triangle.a)) > 1e-10) {
        return false;
    }

    // Calculate areas
    const double area_ABP = 0.5 * length(crossProduct(p - triangle.a, triangle.b - triangle.a));
    const double area_ACP = 0.5 * length(crossProduct(p - triangle.a, triangle.c - triangle.a));
    const double area_BCP = 0.5 * length(crossProduct(p - triangle.b, triangle.c - triangle.b));
    const double area_ABC = 0.5 * length(crossProduct(triangle.b - triangle.a, triangle.c - triangle.a));

    // Check if point is inside the triangle
    return abs(area_ABP + area_ACP + area_BCP - area_ABC) < 1e-10;
}

bool FindIntersectionPoint::findIntersectionPoint(const double x, const double z, Point3D &intersection) const {
    // Calculate t for intersection with plane
    const double t = -(A * x + B * y0S + C * z + D) / (B * dy);

    // Calculate intersection point
    intersection.x = x;
    intersection.y = y0S + t * dy;
    intersection.z = z;

    // Check if intersection point is inside the triangle
    return isPointInTriangle(intersection);
}
