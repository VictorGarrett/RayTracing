#include "mat.h"

// ====================================================//
// Display, Create, Copy

void display_mat(float **m, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      std::cout << m[i][j] << ' ';
    std::cout << '\n';
  }
}

void display_mat(float m[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      std::cout << m[i][j] << ' ';
    std::cout << '\n';
  }
}

float **create_mat(int n) {
  float **m;
  m = new float *[n];
  for (int i = 0; i < n; i++) {
    m[i] = new float[n];
  }

  return m;
}

float **fill_mat(float **m, float n) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      m[i][j] = n;
  }

  return m;
}

float **copy_mat3x3(float m[3][3]) {
  float **mat = create_mat(3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mat[i][j] = m[i][j];
    }
  }

  return mat;
}

float **copy_mat4x4(float m[4][4]) {
  float **mat = create_mat(4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat[i][j] = m[i][j];
    }
  }

  return mat;
}

float **transpose(float mat[4][4]) {
  float **m = create_mat(4);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      m[row][col] = mat[col][row];
    }
  }
  return m;
}

float **transpose(float **mat) {
  float **m = create_mat(4);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      m[row][col] = mat[col][row];
    }
  }
  return m;
}

const bool equal4x4(float m1[4][4], float m2[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      if (m1[i][j] != m2[i][j])
        return false;
  }

  return true;
}

float **get_idt_4x4() {
  float **m = create_mat(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      m[i][j] = i == j ? 1 : 0;
  }

  return m;
}

void free_mat4x4(float **m) {
  for (int i = 0; i < 4; i++)
    delete[] m[i];

  delete[] m;
}

// ====================================================//
// Determinant

const float determinant2x2(float m[2][2]) {
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

const float determinant2x2(float **m) {
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

const float determinant3x3(float m[3][3]) {
  float determinant = 0;
  for (int col = 0; col < 3; col++)
    determinant += m[0][col] * cofactor(m, 0, col);

  return determinant;
}

const float determinant3x3(float **m) {
  float determinant = 0;
  for (int col = 0; col < 3; col++)
    determinant += m[0][col] * cofactor3x3(m, 0, col);

  return determinant;
}

const float determinant4x4(float m[4][4]) {
  float determinant = 0;

  for (int col = 0; col < 4; col++)
    determinant += m[0][col] * cofactor(m, 0, col);

  return determinant;
}

const float determinant4x4(float **m) {
  float determinant = 0;

  for (int col = 0; col < 4; col++)
    determinant += m[0][col] * cofactor4x4(m, 0, col);

  return determinant;
}

// ====================================================//
// Submatrix

float **submatrix3x3(float m[3][3], int r, int c) {
  int skip_row = 0;
  int skip_col = 0;
  float **mat = create_mat(2);
  for (int row = 0; row < 2; row++) {
    if (row == r)
      skip_row = 1;
    for (int col = 0; col < 2; col++) {
      if (col == c && !skip_col)
        skip_col = 1;
      mat[row][col] = m[row + skip_row][col + skip_col];
    }
    skip_col = 0;
  }

  return mat;
}

float **submatrix3x3(float **m, int r, int c) {
  int skip_row = 0;
  int skip_col = 0;
  float **mat = create_mat(2);
  for (int row = 0; row < 2; row++) {
    if (row == r)
      skip_row = 1;
    for (int col = 0; col < 2; col++) {
      if (col == c && !skip_col)
        skip_col = 1;
      mat[row][col] = m[row + skip_row][col + skip_col];
    }
    skip_col = 0;
  }

  return mat;
}

float **submatrix4x4(float m[4][4], int r, int c) {
  int skip_row = 0;
  int skip_col = 0;
  float **mat = create_mat(3);
  for (int row = 0; row < 3; row++) {
    if (row == r)
      skip_row = 1;
    for (int col = 0; col < 3; col++) {
      if (col == c && !skip_col)
        skip_col = 1;
      mat[row][col] = m[row + skip_row][col + skip_col];
    }
    skip_col = 0;
  }

  return mat;
}

float **submatrix4x4(float **m, int r, int c) {
  int skip_row = 0;
  int skip_col = 0;
  float **mat = create_mat(3);
  for (int row = 0; row < 3; row++) {
    if (row == r)
      skip_row = 1;
    for (int col = 0; col < 3; col++) {
      if (col == c && !skip_col)
        skip_col = 1;
      mat[row][col] = m[row + skip_row][col + skip_col];
    }
    skip_col = 0;
  }

  return mat;
}

// ====================================================//
// Minor

const float minor(float mat[3][3], int r, int c) {
  return determinant2x2(submatrix3x3(mat, r, c));
}

const float minor3x3(float **mat, int r, int c) {
  return determinant2x2(submatrix3x3(mat, r, c));
}

const float minor(float mat[4][4], int r, int c) {
  return determinant3x3(submatrix4x4(mat, r, c));
}

const float minor4x4(float **mat, int r, int c) {
  return determinant3x3(submatrix4x4(mat, r, c));
}

// ====================================================//
// Cofactor

const float cofactor(float mat[3][3], int r, int c) {
  float minor_val = minor(mat, r, c);
  return (r + c) % 2 == 0 ? minor_val : -minor_val;
}

const float cofactor3x3(float **mat, int r, int c) {
  float minor_val = minor3x3(mat, r, c);
  return (r + c) % 2 == 0 ? minor_val : -minor_val;
}

const float cofactor(float mat[4][4], int r, int c) {
  float minor_val = minor(mat, r, c);
  return (r + c) % 2 == 0 ? minor_val : -minor_val;
}

const float cofactor4x4(float **mat, int r, int c) {
  float minor_val = minor4x4(mat, r, c);
  return (r + c) % 2 == 0 ? minor_val : -minor_val;
}

// ====================================================//
// Inverse
float **inverse(float mat[4][4]) {
  float **inv = create_mat(4);
  if (determinant4x4(mat) == 0) {
    std::cerr << "the matrix is not invertible" << '\n';
    return inv;
  }

  float det = determinant4x4(mat);
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      float c = cofactor(mat, row, col);
      inv[col][row] = c / det;
    }
  }

  return inv;
}

float **inverse(float **mat) {
  float **inv = create_mat(4);
  if (determinant4x4(mat) == 0) {
    std::cerr << "the matrix is not invertible" << '\n';
    return inv;
  }

  float det = determinant4x4(mat);
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      float c = cofactor4x4(mat, row, col);
      inv[col][row] = c / det;
    }
  }

  return inv;
}

// ====================================================//
// Multiply
float **multiply4x4(float m1[4][4], float m2[4][4]) {
  float **m = create_mat(4);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      m[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] +
                    m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
    }
  }
  return m;
}

float **multiply4x4(float **m1, float **m2) {
  float **m = create_mat(4);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      m[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] +
                    m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
    }
  }
  return m;
}
