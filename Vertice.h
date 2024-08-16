//
// Created by o.narvatov on 8/16/2024.
//

#ifndef VERTICE_H
#define VERTICE_H

#include <ostream>

class Vertice {
public:
    float x = 0;
    float z = 0;
    float y = 0;

    Vertice() = default;
    Vertice(const float _x, const float _z, const float _y) : x(_x), z(_z), y(_y) {}

};

std::ostream& operator<<(std::ostream &os, const Vertice &vector) {
    return os << '(' << vector.x << ", " << vector.z << ", " << vector.y << ')';
}


#endif //VERTICE_H
