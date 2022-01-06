#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "canvas.h"
#include "intersection.h"
#include <list>

class Vec4;

const float PI = 3.14159265359;

// display and other stuff
const void displayErr(std::string str);

void displayVec(const Vec4& v);

void displayColor(const Color& c);

void displayCanvas(const Canvas& c);

void displayIntersections(std::list<Intersection* > list);

const void canvas_to_ppm(const Canvas& c);