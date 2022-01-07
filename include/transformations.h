#pragma once
#include "vec4.h"
#include "mat.h"

float** translation(const float x, const float y, const float z);

float** scaling(const float x, const float y, const float z);

float** rotation_x(float r);

float** rotation_y(float r);

float** rotation_z(float r);

float** shearing(float xy, float xz, float yx, float yz, float zx, float zy);

float** view_transform(const Vec4& from, const Vec4& to, const Vec4& up);