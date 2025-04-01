
#include "Terrain.h"
#include <iostream>
#include "Vertex.h"
#include <fstream>
#include "Perlin.h"

Terrain::Terrain(const int size): size(size) {
    // Resize the 2D vector to the correct size, should be a square grid
    vertices.resize(size,
        std::vector<Vertex>(size,Vertex(0, 0, 0)));
        // correct the coordinates of the vertices
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            /* Set the x and y coordinates of the vertices.
             The x coordinate should be the column number, which is reversed from
             how it normally is in a 2D array. Just leaving it for now,
             so I can keep using xyz intuitively. Normalize to make sure that
             the values are from 0 to 1*/

            vertices[i][j].setX(static_cast<double>(j)/size);
            vertices[i][j].setY(static_cast<double>(i)/size);
        }
    }
}

void Terrain::generateTerrain(const double frequency, const double xOffset, const double yOffset, const int octaves, const double persistence, double lacunarity) {
    //Use the perlin noise generator on each point to generate terrain
    Perlin perlin;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double xInput = vertices[i][j].getX() + xOffset;
            double yInput = vertices[i][j].getY() + yOffset;
            const double noiseValue = perlin.fractalNoise(frequency, xInput, yInput, octaves, persistence, lacunarity);
            vertices[i][j].setZ(noiseValue);
        }
    }
}

void Terrain::normalizeTerrain() {
    // set all x, y, and z values to ranges -1 to 1
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            vertices[i][j].setX(vertices[i][j].getX() / size);
            vertices[i][j].setY(vertices[i][j].getY() / size);
            //vertices[i][j].setZ(vertices[i][j].getZ() / size);
        }
    }

}

void Terrain::smoothTerrain(int iterations) {
    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<std::vector<double>> newZ(size, std::vector<double>(size, 0.0));
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                // Average the z-values of the four direct neighbors
                double average = (vertices[i - 1][j].getZ() +
                                  vertices[i + 1][j].getZ() +
                                  vertices[i][j - 1].getZ() +
                                  vertices[i][j + 1].getZ()) / 4.0;
                newZ[i][j] = average;
            }
        }
        // Update vertices for inner grid points
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                vertices[i][j].setZ(newZ[i][j]);
            }
        }
    }
}


void Terrain::printTerrain() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << "(" << vertices[i][j].getX() << ", " << vertices[i][j].getY() << ") ";
        }
        std::cout << std::endl;
    }
}

void Terrain::printHeights() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << vertices[i][j].getZ() << " ";
        }
        std::cout << std::endl;
    }
}

void Terrain::writeToCSV(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    // Write header row
    out << "x,y,z" << std::endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            out << vertices[i][j].getX() << ","
                << vertices[i][j].getY() << ","
                << vertices[i][j].getZ() << std::endl;
        }
    }
    out.close();
}

void Terrain::writeToOBJ(const std::string &filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    //write using OBJ file format

    //write vertices first
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            out << "v " << vertices[i][j].getX() << " "
                << vertices[i][j].getZ() << " "
                << vertices[i][j].getY() << std::endl;
        }
    }


    //write quad faces next
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            out << "f " << i * size + j + 1 << " "
                << i * size + j + 2 << " "
                << (i + 1) * size + j + 2 << " "
                << (i + 1) * size + j + 1 << std::endl;
        }
    }
}

