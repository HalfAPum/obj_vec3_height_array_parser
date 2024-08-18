//
// Created by o.narvatov on 8/18/2024.
//

#include "Vertice.h"


inline std::ostream& operator<<(std::ostream &os, const Vertice &vector) {
    return os << '(' << vector.x << ", " << vector.z << ", " << vector.y << ')';
}