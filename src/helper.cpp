#include "helper.h"
#include "vec4.h"
#include "intersection.h"

const void displayErr(std::string str) { 
    std::cerr << str;
    exit(0);
}


void displayVec(const Vec4& v) {
    std::string type = v.w ? "point" : "vector";
    std::cout << type << '(' << v.x << ", " << v.y << ", " << v.z << ')' << '\n';
}

void displayColor(const Color& c) {
    std::cout << '(' << c.red << ", " << c.green << ", " << c.blue << ") ";
}

void displayCanvas(const Canvas& c) {
    for(unsigned int i = 0; i < c.height; i++) {
        for(unsigned int j = 0; j < c.width; j++)
            displayColor(c.grid[i][j]);
        std::cout << '\n';
    }
}

void displayIntersections(std::list<Intersection* > list){
    for(auto const& intersection : list)
        std::cout << intersection->t << '\n';
}


const void canvas_to_ppm(const Canvas& c) {
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