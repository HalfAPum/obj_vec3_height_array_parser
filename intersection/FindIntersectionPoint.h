//
// Created by o.narvatov on 8/17/2024.
//

#ifndef FINDINTERSECTIONPOINT_H
#define FINDINTERSECTIONPOINT_H
#include "Triangle.h"

using namespace std;

constexpr double y0S = 0.0; // Arbitrary starting y
constexpr double dy = 1.0; // Direction vector in y

//Class and classes that it use are based on normal x,y,z coordinate.
class FindIntersectionPoint {

    Triangle triangle;
    Point3D normal;
    double A = 0.0;
    double B = 0.0;
    double C = 0.0;
    double D = 0.0;

public:
    explicit FindIntersectionPoint(const Triangle& _triangle) : triangle(_triangle) {
        normal = crossProduct(_triangle.b - _triangle.a, _triangle.c - _triangle.a);

        // Plane equation coefficients
        A = normal.x;
        B = normal.y;
        C = normal.z;
        D = -dotProduct(normal, _triangle.a);
    }


    static double dotProduct(const Point3D& v1, const Point3D& v2);

    static Point3D crossProduct(const Point3D& v1, const Point3D& v2);

    [[nodiscard]] inline bool isPointInTriangle(const Point3D& p) const;

    bool findIntersectionPoint(double x, double z, Point3D& intersection) const;

};



#endif //FINDINTERSECTIONPOINT_H
