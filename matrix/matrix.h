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
Matrix identity_matrix();

// matrix comparison
bool compareMatrix(Matrix a, Matrix b); 
Matrix matrixMultiply(Matrix a, Matrix b);
Tuple multiply(const Matrix& m, const Tuple& t);
Matrix transpose(const Matrix& m); 
double determinant(const Matrix& m); 
Matrix submatrix(const Matrix& m, int row, int col); 
double minor(const Matrix& m, int row, int col);
double cofactor(const Matrix& m, int row, int col);
bool is_invertible(const Matrix& m);
Matrix inverse(const Matrix& m);
Matrix translation(double x, double y, double z);
Matrix scaling(double x, double y, double z); 
#endif // MATRIX_H

