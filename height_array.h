#ifndef HEIGHTARRAY_H
#define HEIGHTARRAY_H

#include <ostream>
#include <array>

using namespace std;

const string OBJ_EXT = ".obj";
const string TEXT_EXT = ".txt";

constexpr int FLOAT_PRECISION = 100;
constexpr int MAP_SIZE_H_A = 256;
constexpr int Z_AXIS_PRECISION = 10;
constexpr int PRECISED_MAP_SIZE = MAP_SIZE_H_A * Z_AXIS_PRECISION + 1;
constexpr float PRECISION_STEP = 1.0 / Z_AXIS_PRECISION;

using z_axis_array = array<array<float, PRECISED_MAP_SIZE>, PRECISED_MAP_SIZE>;

class Height_Array {
public:
    void print_array(z_axis_array* height_array, ostream &os);

    void write_array_to_file(z_axis_array* height_array, const string &file_name);

    z_axis_array* get_height_array();
};

#endif