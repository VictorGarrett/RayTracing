#include "canvas.h"
#include "sphere.h"
#include "intersection.h"
#include "mat.h"

// display and other stuff
void displayVec(const Vec4& v) {
    std::cout << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')' << '\n';
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

int main() {
    float A[4][4] = {
        {9,3,0,9},
        {-5,-2,-6,-3},
        {-4,9,6,4},
        {-7,6,6,2}
    };

    float B[4][4] = {
        {8,2,2,2},
        {3,-1,7,0},
        {7, 0,5,4},
        {6,-2,0,2}
    };

    float **C = multiply4x4(A, B);

    float **invB = inverse(B);

    // display_mat(C, 4);
    // std::cout << std::endl;
    // display_mat(invB, 4);

    // std::cout << std::endl;

    float **nA = multiply4x4(C, invB);
    display_mat(nA, 4);
    return 0;
}

