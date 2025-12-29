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
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (std::abs(data[i][j] - other.data[i][j]) >= EPSILON) {
                return false;
            }
        }
    }
    
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
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

