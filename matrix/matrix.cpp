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

