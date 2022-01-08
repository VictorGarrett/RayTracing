#pragma once 
#include "color.h"

class Canvas {
public:
    unsigned int width;
    unsigned int height;
    Color** grid;

    Canvas();
    Canvas(const unsigned int w, const unsigned int h);
    ~Canvas();

    void fill_grid(const Color& c);
    void write_pixel(const unsigned int pos_x, const unsigned int pos_y, const Color& c);
    const Color pixel_at(const unsigned int pos_x, const unsigned int pos_y) const;
};