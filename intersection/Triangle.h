//
// Created by o.narvatov on 8/17/2024.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point3D.h"
#include "../Vertice.h"


struct Triangle {
    Point3D a, b, c;

    Triangle(
        const Vertice &vertice1,
        const Vertice &vertice2,
        const Vertice &vertice3
    ) : a(vertice1), b(vertice2), c(vertice3) {}

};

#endif //TRIANGLE_H
