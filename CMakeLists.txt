cmake_minimum_required(VERSION 3.28)
project(gltf_plus_binary_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(gltf_plus_binary_parser main.cpp
        Face.h
        Vertice.h
        intersection/Triangle.h
        intersection/Point3D.h
        intersection/FindIntersectionPoint.cpp
)