cmake_minimum_required(VERSION 3.30)
project(Terrain)

set(CMAKE_CXX_STANDARD 26)

add_executable(Terrain main.cpp
        Vertex.cpp
        Vertex.h
        Terrain.cpp
        Terrain.h
        Perlin.cpp
        Perlin.h)
