
#include "Perlin.h"
#include <cmath>
#include <iostream>

Perlin::Perlin() {
    // Initialize the permutation vector
    perm.resize(512);
    for (int i = 0; i < 512; i++) {
        perm[i] = permutations[i%256];
    }
}

void Perlin::printPermutations() const {
    for (int i = 0; i < 512; i++) {
        std::cout << perm[i] << " ";
    }
    std::cout << std::endl;
}

double Perlin::fade(const double t) {
    // Fade function as defined by Ken Perlin
    return 6*pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
}

double Perlin::lerp(const double a, const double b, const double t) {
    return a + t * (b - a);
}

double Perlin::dot_product(const double x, const double y, const double x1, const double y1) {
    return x * x1 + y * y1;
}

std::vector<double> Perlin::getGradient(const double x, const double y) {
    // Get the gradient vector for the given x and y based on the permutations
    const int xi = static_cast<int>(floor(x)) % 256;
    const int yi = static_cast<int>(floor(y)) % 256;

    const int hash = perm[perm[xi] + yi];

    const int index = hash & 7;

    return gradients[index];
}

double Perlin::generateNoise(double x, double y) {
    // Identify the unit square that the point falls in
    const int x0 = static_cast<int>(floor(x));
    const int x1 = x0 + 1;
    const int y0 = static_cast<int>(floor(y));
    const int y1 = y0 + 1;

    //retrieve the gradient vectors for each corner of the unit square
    const std::vector<double> grad00 = getGradient(x0, y0);
    const std::vector<double> grad10 = getGradient(x1, y0);
    const std::vector<double> grad01 = getGradient(x0, y1);
    const std::vector<double> grad11 = getGradient(x1, y1);

    //find dot products between the gradients and the vectors from the corners to the point
    const double dot00 = dot_product(grad00[0], grad00[1], x - x0, y - y0);
    const double dot10 = dot_product(grad10[0], grad10[1], x - x1, y - y0);
    const double dot01 = dot_product(grad01[0], grad01[1], x - x0, y - y1);
    const double dot11 = dot_product(grad11[0], grad11[1], x - x1, y - y1);

    //Fade the fractional parts
    const double u = fade(x - x0);
    const double v = fade(y - y0);

    //lerp results
    const double x0_lerp = lerp(dot00, dot10, u);
    const double x1_lerp = lerp(dot01, dot11, u);

    return lerp(x0_lerp, x1_lerp, v);


}

double Perlin::fractalNoise(double inputFrequency, double x, double y, int octaves, double persistence, double lacunarity) {
    double total = 0;
    double amplitude = 1;
    double maxAmplitude = 0;

    for (int i = 0; i < octaves; i++) {
        total += generateNoise(x * inputFrequency, y * inputFrequency) * amplitude;

        maxAmplitude += amplitude;

        amplitude *= persistence;
        inputFrequency *= lacunarity;
    }
    //For debugging purposes
    //std::cout << total << std::endl;
    return total / maxAmplitude;
}

