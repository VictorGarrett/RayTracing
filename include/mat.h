#pragma once 
#include <iostream>
#include "vec4.h"

// float _matrix[4][4] = {
//     {1,0,0,0},
//     {0,1,0,0},
//     {0,0,1,0},
//     {0,0,0,1}
// };

// Display, Create, Copy, Equal, Transpose
void display_mat(float **m, int n);

void display_mat(float m[4][4]);

float** create_mat(int n);

float** copy_mat3x3(float m[3][3]);

const bool equal4x4(float m1[4][4], float m2[4][4]);

float** transpose(float mat[4][4]);

// Determinant
const float determinant2x2(float m[2][2]);

const float determinant2x2(float **m);

const float determinant3x3(float m[3][3]);

const float determinant3x3(float **m);

const float determinant4x4(float m[4][4]);

const float determinant4x4(float **m);


// Submatrix
float** submatrix4x4(float m[4][4], int r, int c);

float** submatrix3x3(float m[3][3], int r, int c);

float** submatrix3x3(float **m, int r, int c);


// Minor
const float minor(float mat[3][3], int r, int c);

const float minor(float **mat, int r, int c);

const float minor(float mat[4][4], int r, int c);

// Cofactor
const float cofactor(float mat[3][3], int r, int c);

const float cofactor(float **mat, int r, int c);

const float cofactor(float mat[4][4], int r, int c);

// Inverse
float** inverse(float mat[4][4]);

float** inverse(float **mat);

// Multiply
float** multiply4x4(float m1[4][4], float m2[4][4]);

float** multiply4x4(float **m1, float **m2);

Vec4 multiplyMatVec4(float m[4][4], const Vec4& v);
