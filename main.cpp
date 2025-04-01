#include "Terrain.h"
#include "Vertex.h"
#include <iostream>

#include "Perlin.h"

int main(int argc, char* argv[]) {
    // Check that the correct number of arguments is provided
    if(argc < 6) {
        std::cerr << "Usage: " << argv[0] << " <frequency> <resolution> <offset>" << std::endl;
        return 1;
    }

    const double frequency = std::stod(argv[1]);
    const int resolution = std::stoi(argv[2]);
    const double xoffset = std::stod(argv[3]);
    const double yoffset = std::stod(argv[4]);
    const int octaves = std::stoi(argv[5]);
    const double persistence = std::stod(argv[6]);
    const double lacunarity = std::stod(argv[7]);
    const int export_obj = std::stoi(argv[8]);
    Terrain landscape(resolution);
    std::cout << "Terrain created with size " << landscape.getSize() << std::endl;

    landscape.generateTerrain(frequency, xoffset, yoffset, octaves, persistence, lacunarity);


    landscape.writeToCSV("csvs/terrain.csv");
    if (export_obj != 0) {
        landscape.writeToOBJ("objs/terrain.obj");
    }

}
