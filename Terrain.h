
#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "Vertex.h"
#include <string>


// Terrain class, which stores a 2D grid of vertices

class Terrain {
public:
    explicit Terrain(int size); //
    [[nodiscard]] int getSize() const {return size;}
    [[nodiscard]] const Vertex& getVertex(const int x, int y) const {return vertices[y][x];}
    void setVertex(const int x, int y, const Vertex& v) {vertices[y][x] = v;}


    void printTerrain() const;
    void printHeights() const;
    void writeToCSV(const std::string& filename) const;
    void writeToOBJ(const std::string& filename) const;

    void generateTerrain(double frequency, double xOffset, double yOffset, int octaves, double persistence, double lacunarity); //use perlin class to generate noise
    void normalizeTerrain(); //normalize the terrain so that the highest point is 1 and the lowest point is -1, for all 3 axes
    void smoothTerrain(int iterations); //use laplacian smoothing to increase grid resolution without affecting scale


private:
    int size; //Grid should be a size x size grid
    std::vector<std::vector<Vertex>> vertices;

};



#endif //TERRAIN_H
