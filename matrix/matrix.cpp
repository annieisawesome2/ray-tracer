#include "matrix.h"
#include <cmath>

Matrix::Matrix(int rows, int cols) 
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols, 0.0)) {
}

Matrix::Matrix(int rows, int cols, const std::vector<std::vector<double>>& values)
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols, 0.0)) {
    for (int i = 0; i < rows && i < static_cast<int>(values.size()); i++) {
        for (int j = 0; j < cols && j < static_cast<int>(values[i].size()); j++) {
            data[i][j] = values[i][j];
        }
    }
}

double& Matrix::operator()(int row, int col) {
    return data[row][col];
}

const double& Matrix::operator()(int row, int col) const {
    return data[row][col];
}

bool Matrix::operator==(const Matrix& other) const {
    return compareMatrix(*this, other);
}

bool Matrix::operator!=(const Matrix& other) const {
    return !compareMatrix(*this, other);
}

// Factory functions
Matrix matrix4x4(const std::vector<std::vector<double>>& values) {
    return Matrix(4, 4, values);
}

Matrix matrix3x3(const std::vector<std::vector<double>>& values) {
    return Matrix(3, 3, values);
}

Matrix matrix2x2(const std::vector<std::vector<double>>& values) {
    return Matrix(2, 2, values);
}

Matrix identity_matrix() {
    // 4x4 identity matrix: 1s on diagonal, 0s elsewhere
    return matrix4x4({
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });
}

bool compareMatrix(Matrix a, Matrix b) {
    // Compare if matrix a rows and columns match matrix b's
    if (a.rows != b.rows || a.cols != b.cols) {
        return false;
    }
    
    // Compare each element using EPSILON for floating point comparison
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (std::abs(a.data[i][j] - b.data[i][j]) >= EPSILON) {
                return false;
            }
        }
    }
    
    return true;
}

Matrix matrixMultiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        return Matrix(0, 0);
    }
    
    Matrix result(a.rows, b.cols);

    for (int row = 0; row < result.rows; row++) {
        for (int col = 0; col < result.cols; col++) {
            double sum = 0.0;
            // Compute: A[row, k] * B[k, col] for all k
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[row][k] * b.data[k][col];
            }
            result.data[row][col] = sum;
        }
    }
    
    return result;
}

Tuple multiply(const Matrix& m, const Tuple& t) {
    // Treat tuple as a 4x1 column matrix and multiply
    // For each row in the matrix, compute dot product with the tuple
    double x = m.data[0][0] * t.x + m.data[0][1] * t.y + m.data[0][2] * t.z + m.data[0][3] * t.w;
    double y = m.data[1][0] * t.x + m.data[1][1] * t.y + m.data[1][2] * t.z + m.data[1][3] * t.w;
    double z = m.data[2][0] * t.x + m.data[2][1] * t.y + m.data[2][2] * t.z + m.data[2][3] * t.w;
    double w = m.data[3][0] * t.x + m.data[3][1] * t.y + m.data[3][2] * t.z + m.data[3][3] * t.w;
    
    return Tuple(x, y, z, w);
}

Matrix transpose(const Matrix& m) {
    // Transpose: swap rows and columns
    // Element at [i, j] becomes element at [j, i]
    Matrix result(m.cols, m.rows);
    
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];
        }
    }
    
    return result;
}

double determinant(const Matrix& m) {
    // For a 2x2 matrix: determinant = a*d - b*c
    if (m.rows == 2 && m.cols == 2) {
        return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
    }
    
    // For larger matrices: use first row and cofactors
    double det = 0.0;
    for (int col = 0; col < m.cols; col++) {
        det += m.data[0][col] * cofactor(m, 0, col);
    }
    
    return det;
}

Matrix submatrix(const Matrix& m, int row, int col) {
    Matrix sub(m.rows - 1, m.cols - 1);

    int sub_row = 0; 
    for (int i = 0; i < m.rows; i++) {
        if (i == row)
            continue; 

        int sub_column = 0; 
        for (int j = 0; j < m.cols; j++) {
            if (j == col) 
                continue; 

            sub.data[sub_row][sub_column] = m.data[i][j]; 
            sub_column++; 
        }
        sub_row++; 
    }
    return sub; 
}

double minor(const Matrix& m, int row, int col) {
    Matrix A = submatrix(m, row, col); 
    return determinant(A); 
}

double cofactor(const Matrix& m, int row, int col) {
    double min = minor(m, row, col);
    // If row + col is odd, negate the minor; otherwise keep it as is
    if ((row + col) % 2 == 1) {
        return -min;
    }
    return min;
}

bool is_invertible(const Matrix& m) {
    // A matrix is invertible if its determinant is not zero
    return std::abs(determinant(m)) >= EPSILON;
}

Matrix inverse(const Matrix& m) {
    // Fail if matrix is not invertible
    if (!is_invertible(m)) {
        // Return empty matrix as error indicator
        return Matrix(0, 0);
    }
    
    double det = determinant(m);
    Matrix result(m.rows, m.cols);
    
    // For each row and column, compute cofactor and divide by determinant
    // Store at [col, row] to accomplish transpose operation
    for (int row = 0; row < m.rows; row++) {
        for (int col = 0; col < m.cols; col++) {
            double c = cofactor(m, row, col);
            result.data[col][row] = c / det;
        }
    }
    
    return result;
}

Matrix translation(double x, double y, double z) {
    // Translation matrix: identity matrix with x, y, z in the last column
    Matrix result = identity_matrix();
    result.data[0][3] = x;
    result.data[1][3] = y;
    result.data[2][3] = z;
    return result;
}

Matrix scaling(double x, double y, double z) {
    // Scaling matrix: scaling factors on the diagonal
    Matrix result = identity_matrix();
    result.data[0][0] = x;
    result.data[1][1] = y;
    result.data[2][2] = z;
    return result;
}

Matrix rotation_x(double radians) {
    // Rotation matrix around x-axis by r radians:
    // [1,     0,        0,     0]
    // [0,  cos r,  -sin r,     0]
    // [0,  sin r,   cos r,     0]
    // [0,     0,        0,     1]
    Matrix result = identity_matrix();
    double cos_r = std::cos(radians);
    double sin_r = std::sin(radians);
    result.data[1][1] = cos_r;
    result.data[1][2] = -sin_r;
    result.data[2][1] = sin_r;
    result.data[2][2] = cos_r;
    return result;
}

Matrix rotation_y(double radians) {
    // Rotation matrix around y-axis by r radians:
    // [cos r,  0,  sin r,  0]
    // [0,      1,  0,      0]
    // [-sin r, 0,  cos r,  0]
    // [0,      0,  0,      1]
    Matrix result = identity_matrix();
    double cos_r = std::cos(radians);
    double sin_r = std::sin(radians);
    result.data[0][0] = cos_r;
    result.data[0][2] = sin_r;
    result.data[2][0] = -sin_r;
    result.data[2][2] = cos_r;
    return result;
}
