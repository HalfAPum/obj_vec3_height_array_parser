//
// Created by o.narvatov on 8/17/2024.
//

#ifndef POINT3D_H
#define POINT3D_H


struct Point3D {
    double x, y, z;

    Point3D operator-(const Point3D &other) const {
        Point3D np {};
        np.x = x - other.x;
        np.y = y - other.y;
        np.z = z - other.z;
        return np;
    }
};


#endif //POINT3D_H
