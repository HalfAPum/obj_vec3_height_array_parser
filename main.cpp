#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <array>
#include <sstream>

#include "Face.h"
#include "Vertice.h"
#include "intersection/FindIntersectionPoint.h"

using namespace std;

const string OBJ_EXT = ".obj";
const string TEXT_EXT = ".txt";

constexpr int FLOAT_PRECISION = 100;
constexpr int MAP_SIZE = 8;
constexpr int Z_AXIS_PRECISION = 2;
constexpr int PRECISED_MAP_SIZE = MAP_SIZE * Z_AXIS_PRECISION + 1;
constexpr float PRECISION_STEP = 1.0 / Z_AXIS_PRECISION;

//final array
array<array<float, PRECISED_MAP_SIZE>, PRECISED_MAP_SIZE> height_array {};

int get_vertice_index(string &vertice) {
    //Substract 1 because vector is 0-based.
    return stoi(vertice.substr(0, vertice.find('/'))) - 1;
}

void parse_obj_file(const string &file_name, vector<Vertice> &verticeCoordinates, vector<Face> &faceVerticeIndecies) {
    ifstream map_obj_file (file_name + OBJ_EXT);
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

            faceVerticeIndecies.emplace_back(
                get_vertice_index(vertice1),
                get_vertice_index(vertice2),
                get_vertice_index(vertice3)
            );
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
    const auto vertice3 = verticeCoordinates[face.vertice3_index];

    // cout << vertice1 << endl;
    // cout << vertice2 << endl;
    // cout << vertice3 << endl;

    const float min_x = min(vertice1.x, min(vertice2.x, vertice3.x));
    const float max_x = max(vertice1.x, max(vertice2.x, vertice3.x));

    const float min_y = min(vertice1.y, min(vertice2.y, vertice3.y));
    const float max_y = max(vertice1.y, max(vertice2.y, vertice3.y));

    const FindIntersectionPoint find_intersection(Triangle(vertice1, vertice2, vertice3));

    for (float i = min_x;; i = min(max_x, i + PRECISION_STEP)) {
        const int i_index = (i * Z_AXIS_PRECISION);

        for (float j = min_y;; j = min(max_y, j + PRECISION_STEP)) {
            const int j_index = (j * Z_AXIS_PRECISION);

            if (height_array[i_index][j_index] != 0.0) {
                if (j == max_y) break;
                continue;
            }

            // cout << i << ' ' << j << endl;

            Point3D intersection {};

            if (find_intersection.findIntersectionPoint(i, j, intersection)) {
                height_array[i_index][j_index] = intersection.y;
                // cout << "Intersection point: (" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << endl;
            } else {
                // cout << "No intersection" << endl;
            }

            if (j == max_y) break;
        }
        if (i == max_x) break;
    }
}

void print_array(ostream &os) {
    for (auto arr : height_array) {
        for (auto e : arr) {
            auto rounded = roundf(e * FLOAT_PRECISION) / FLOAT_PRECISION;

            ostringstream oss;
            oss << rounded;
            string rs = oss.str();

            os << rs;

            if (rs.size() < 4) {
                auto i = rs.size();
                if (rs.find('.') == std::string::npos) {
                    os << '.';
                    ++i;
                }

                for (;i<4; ++i) {
                    os << 0;
                }
            }

            os << ' ';
        }
        os << endl;
    }
}

const string METADATA = "METADATA";
const string METADATA_MAP_SIZE = "MAP_SIZE ";
const string METADATA_Z_AXIS_PRECISION = "Z_AXIS_PRECISION ";
const string METADATA_PRECISED_MAP_SIZE = "PRECISED_MAP_SIZE ";
const string METADATA_PRECISION_STEP = "PRECISION_STEP ";

void write_array_to_file(const string &file_name) {
    ofstream file (file_name + TEXT_EXT);

    file << METADATA << endl;
    file << METADATA_MAP_SIZE << MAP_SIZE << endl;
    file << METADATA_Z_AXIS_PRECISION << Z_AXIS_PRECISION << endl;
    file << METADATA_PRECISED_MAP_SIZE << PRECISED_MAP_SIZE << endl;
    file << METADATA_PRECISION_STEP << PRECISION_STEP << endl;
    file << METADATA << endl;

    file << endl;

    print_array(file);
}

int main() {
    vector<Vertice> verticeCoordinates;
    vector<Face> faceVerticeIndecies;

    const string file_name = "pos_normal1";

    parse_obj_file(file_name, verticeCoordinates, faceVerticeIndecies);

    transform_verticie_coordinates_to_map_scale(verticeCoordinates, MAP_SIZE);

    for (auto &face : faceVerticeIndecies) {
        fill_height_array(verticeCoordinates, face);
    }

    write_array_to_file(file_name);
}