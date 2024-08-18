//
// Created by o.narvatov on 8/16/2024.
//

#ifndef FACE_H
#define FACE_H

#include <ostream>

class Face {
public:
    int vertice1_index = 0;
    int vertice2_index = 0;
    int vertice3_index = 0;

    Face() = default;
    Face(
        const int _vertice1_index,
        const int _vertice2_index,
        const int _vertice3_index
    ) :
    vertice1_index(_vertice1_index),
    vertice2_index(_vertice2_index),
    vertice3_index(_vertice3_index)
    {}

};

std::ostream& operator<<(std::ostream &os, const Face &face);

#endif //FACE_H
