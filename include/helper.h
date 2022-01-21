#pragma once
#include "canvas.h"
#include "constants.h"
#include "intersection.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

class Vec4;

// display and other stuff
const void displayErr(std::string str);

void displayVec(const Vec4 &v);

void displayColor(const Color &c);

void displayCanvas(const Canvas &c);

void displayIntersections(std::list<Intersection *> list);

const void canvas_to_ppm(const Canvas &c);

// OBJ parser
