#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

constexpr int FLOAT_PRECISION = 10000;

class Vector3 {
public:
    float x = 0;
    float z = 0;
    float y = 0;

    Vector3() = default;
    Vector3(const float _x, const float _z, const float _y) : x(_x), z(_z), y(_y) {}

};

ostream& operator<<(ostream &os, const Vector3 &vector) {
    return os << '(' << vector.x << ", " << vector.z << ", " << vector.y << ')';
}

void parse_3D_object(vector<Vector3> &vector3s) {
    std::string binFilename = "untitled2.bin";

    // Open it with the cursor at the end of the file so we can determine it's size,
    // We could techincally read the filesize from the gltf file, but I trust the file itself more
    std::ifstream binFile = std::ifstream(binFilename, std::ios::binary | std::ios::ate);

    // Read file length and then reset cursor
    size_t binLength = binFile.tellg();
    binFile.seekg(0);


    std::vector<char> bin(binLength);
    binFile.read(bin.data(), binLength);
    binFile.close();

    // Now get the start of the float3 array by adding the bufferView byte offset to the bin pointer
    // It's a little sketchy to cast to a raw float array, but hey, it works.
    float* buffer = (float*)(bin.data());

    // Print out all the vertex positions
    for (int i = 0; i < 12; ++i)
    {
        vector3s.emplace_back(
            roundf(buffer[i*3] * FLOAT_PRECISION) / FLOAT_PRECISION,
            roundf(buffer[i*3+1] * FLOAT_PRECISION) / FLOAT_PRECISION,
            roundf(buffer[i*3+2] * FLOAT_PRECISION) / FLOAT_PRECISION
        );
    }
}

int main()
{
    vector<Vector3> vector3s;

    parse_3D_object(vector3s);

    //find min/max
    float min_x = vector3s[0].x;
    float min_z = vector3s[0].z;
    float min_y = vector3s[0].y;

    float max_x = vector3s[0].x;
    float max_z = vector3s[0].z;
    float max_y = vector3s[0].y;

    for (auto &vector3: vector3s) {
        //min
        min_x = min(min_x, vector3.x);
        min_z = min(min_z, vector3.z);
        min_y = min(min_y, vector3.y);

        //max
        max_x = max(max_x, vector3.x);
        max_z = max(max_z, vector3.z);
        max_y = max(max_y, vector3.y);
    }

    //Convert vector3s from local 0,0,0 center to 0,0,0 start
    for (auto &vector : vector3s) {
        vector.x -= min_x;
        vector.z -= min_z;
        vector.y -= min_y;
    }

    for (auto &vector : vector3s) {
        cout << vector << endl;
    }

    return 0;
}