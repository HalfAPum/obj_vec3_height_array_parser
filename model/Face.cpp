//
// Created by o.narvatov on 8/18/2024.
//

#include "Face.h"

std::ostream& operator<<(std::ostream &os, const Face &face) {
    return os << '(' << face.vertice1_index << ", " << face.vertice2_index << ", " << face.vertice3_index << ')';
}