#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "canvas.h"
#define EPSILON 0.00001

// helper functions
inline const float abs(float n) { return n > 0.f ? n : -n; }
inline const bool equal(float a, float b) { return abs(a-b) < EPSILON; }
inline const void displayErr(std::string str) { 
    std::cerr << str;
    exit(0);
}
inline const void canvas_to_ppm(const Canvas& c) {
    std::ofstream img("blyat.ppm");

    // header
    img << "P3\n";
    img << c.width << ' ' << c.height << "\n";
    img << "255\n";

    // content
    for(int i = c.height - 1; i >= 0; i--) {
        for(unsigned int j = 0; j < c.width; j++)
            img << floor(255 * c.grid[i][j].red) << ' ' 
                << floor(255 * c.grid[i][j].green) << ' ' 
                << floor(255 * c.grid[i][j].blue) << '\n';
    }
}