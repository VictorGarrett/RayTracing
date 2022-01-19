#include "canvas.h"
#include <iostream>

Canvas::Canvas() {}

Canvas::Canvas(const unsigned int w, const unsigned int h) {
    this->width = w;
    this->height = h;

    this->grid = new Color * [h];
    for (unsigned int i = 0; i < h; i++) {
        this->grid[i] = new Color[w];
    }

    this->fill_grid(Color(0, 0, 0));

}
Canvas::~Canvas() {
    delete grid;
}

void Canvas::fill_grid(const Color& c) {
    for (unsigned int i = 0; i < this->height; i++) {
        for (unsigned int j = 0; j < this->width; j++) {
            this->grid[i][j] = c;
        }
    }

}

void Canvas::write_pixel(const unsigned int pos_x, const unsigned int pos_y, const Color& c) {
    this->grid[pos_y][pos_x] = c;
}

const Color Canvas::pixel_at(const unsigned int pos_x, const unsigned int pos_y) const {
    return this->grid[pos_y][pos_x];
}