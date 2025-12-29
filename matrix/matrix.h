#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "tuple/tuple.h"

class Matrix {
public:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

    // Constructor for creating a matrix of specified size (initialized to 0)
    Matrix(int rows, int cols);
    
    // Constructor for creating a matrix from initializer list
    Matrix(int rows, int cols, const std::vector<std::vector<double>>& values);
    
    // Access element at [row, col]
    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;
    
    // Equality operators
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};

// Factory functions for creating matrices
Matrix matrix4x4(const std::vector<std::vector<double>>& values);
Matrix matrix3x3(const std::vector<std::vector<double>>& values);
Matrix matrix2x2(const std::vector<std::vector<double>>& values);

#endif // MATRIX_H

