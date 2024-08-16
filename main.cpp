#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <array>

#include "Face.h"
#include "Vertice.h"

using namespace std;

constexpr int FLOAT_PRECISION = 10000;
constexpr int MAP_SIZE = 16;
constexpr int Z_AXIS_PRECISION = 2;
constexpr float PRECISION_STEP = 1.0 / Z_AXIS_PRECISION;

//final array
array<array<float, MAP_SIZE * Z_AXIS_PRECISION>, MAP_SIZE * Z_AXIS_PRECISION> height_array {};

void parse_obj_file(vector<Vertice> &verticeCoordinates, vector<Face> &faceVerticeIndecies) {
    ifstream map_obj_file ("pos_normal1.obj");
    //string because work can start with that char and stream will break later
    string first_char;

    while (map_obj_file >> first_char) {
        if (first_char == "v") {
            //Vertice

            float x = 0.0;
            float z = 0.0;
            float y = 0.0;

            map_obj_file >> x >> z >> y;

            verticeCoordinates.emplace_back(x, z ,y);
        } else if (first_char == "f") {
            //Face

            string vertice1;
            string vertice2;
            string vertice3;

            map_obj_file >> vertice1 >> vertice2 >> vertice3;

            //Substract 48 to get real number. Substract 1 because vector is 0-based.
            int vertice1_index = vertice1[0] - 48 - 1;
            int vertice2_index = vertice2[0] - 48 - 1;
            int vertice3_index = vertice3[0] - 48 - 1;

            faceVerticeIndecies.emplace_back(vertice1_index, vertice2_index, vertice3_index);
        } else {
            //skip line
            map_obj_file.ignore(numeric_limits<streamsize>::max(), map_obj_file.widen('\n'));
        }
    }
}

void transform_verticie_coordinates_to_map_scale(vector<Vertice> &verticeCoordinates, const int map_size) {
    //find min/max
    float min_x = verticeCoordinates[0].x;
    float min_z = verticeCoordinates[0].z;
    float min_y = verticeCoordinates[0].y;

    //Prevent division by zero
    float max_x = 1;
    float max_z = 1;
    float max_y = 1;

    for (auto &vertice: verticeCoordinates) {
        //min
        min_x = min(min_x, vertice.x);
        min_z = min(min_z, vertice.z);
        min_y = min(min_y, vertice.y);

        //max
        max_x = max(max_x, vertice.x);
        max_z = max(max_z, vertice.z);
        max_y = max(max_y, vertice.y);
    }

    //Since real minumum will be unpdated in next loop update real maximum respectively
    max_x -= min_x;
    max_z -= min_z;
    max_y -= min_y;

    for (auto &vector : verticeCoordinates) {
        //Convert verticeCoordinates from local 0,0,0 center to 0,0,0 start
        vector.x -= min_x;
        vector.z -= min_z;
        vector.y -= min_y;

        //Convert verticeCoordinates to MAP_SIZE scale
        vector.x = vector.x / max_x * map_size;
        vector.z = vector.z / max_z * map_size;
        vector.y = vector.y / max_y * map_size;
    }
}

void fill_height_array(const vector<Vertice> &verticeCoordinates, const Face &face) {
    const auto vertice1 = verticeCoordinates[face.vertice1_index];
    const auto vertice2 = verticeCoordinates[face.vertice2_index];
    auto vertice3 = verticeCoordinates[face.vertice3_index];

    const float min_x = min(vertice1.x, vertice2.x);
    const float max_x = max(vertice1.x, vertice2.x);

    const float min_y = min(vertice1.y, vertice2.y);
    const float max_y = max(vertice1.y, vertice2.y);

    for (auto e : verticeCoordinates) {
        cout << e << endl;
    }

    cout << "---------------" << endl;
    cout << min_x << endl;
    cout << max_x << endl;
    cout << min_y << endl;
    cout << max_y << endl;

    for (float i = min_x;; i = min(max_x, i + PRECISION_STEP)) {
        for (float j = min_y;; j = min(max_y, j + PRECISION_STEP)) {
            cout << i << j << endl;
            // const int i_index = i * Z_AXIS_PRECISION;
            // const int j_index = j * Z_AXIS_PRECISION;
            // if (height_array[i_index][j_index] != 0.0) {
            //     if (j == max_y) break;
            //
            //     continue;
            // }
    //
    //         height_array[i_index][j_index] = vertice1.z;
    //
    //         //do real calculation of height at this point here
                if (j == max_y) break;
            }
    //
        if (i == max_x) break;
    }
}

int main() {
    vector<Vertice> verticeCoordinates;
    vector<Face> faceVerticeIndecies;

    parse_obj_file(verticeCoordinates, faceVerticeIndecies);

    transform_verticie_coordinates_to_map_scale(verticeCoordinates, MAP_SIZE);

    // for (auto &face : faceVerticeIndecies) {
        fill_height_array(verticeCoordinates, faceVerticeIndecies[0]);
    // }

    for (auto arr : height_array) {
        for (auto e : arr) {
            cout << e << ' ';
        }
        cout << endl;
    }

}