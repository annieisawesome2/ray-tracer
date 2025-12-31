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

