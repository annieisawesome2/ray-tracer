#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "matrix/matrix.h"
#include "tuple/tuple.h"

TEST_CASE("Constructing and inspecting a 4x4 matrix", "[matrix]") {
    Matrix M = matrix4x4({
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    });
    
    REQUIRE(equal(M(0, 0), 1));
    REQUIRE(equal(M(0, 3), 4));
    REQUIRE(equal(M(1, 0), 5.5));
    REQUIRE(equal(M(1, 2), 7.5));
    REQUIRE(equal(M(2, 2), 11));
    REQUIRE(equal(M(3, 0), 13.5));
    REQUIRE(equal(M(3, 2), 15.5));
}

TEST_CASE("A 2x2 matrix ought to be representable", "[matrix]") {
    Matrix M = matrix2x2({
        {-3, 5},
        {1, -2}
    });
    
    REQUIRE(equal(M(0, 0), -3));
    REQUIRE(equal(M(0, 1), 5));
    REQUIRE(equal(M(1, 0), 1));
    REQUIRE(equal(M(1, 1), -2));
}

TEST_CASE("A 3x3 matrix ought to be representable", "[matrix]") {
    Matrix M = matrix3x3({
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    });
    
    REQUIRE(equal(M(0, 0), -3));
    REQUIRE(equal(M(1, 1), -2));
    REQUIRE(equal(M(2, 2), 1));
}

TEST_CASE("compareMatrix: A = B with identical matrices", "[matrix]") {
    Matrix A = matrix4x4({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    
    Matrix B = matrix4x4({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    
    REQUIRE(compareMatrix(A, B) == true);
}

TEST_CASE("compareMatrix: A != B with different matrices", "[matrix]") {
    Matrix A = matrix4x4({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    
    Matrix B = matrix4x4({
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    });
    
    REQUIRE(compareMatrix(A, B) == false);
}

TEST_CASE("Multiplying two matrices", "[matrix]") {
    Matrix A = matrix4x4({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    
    Matrix B = matrix4x4({
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}
    });
    
    Matrix expected = matrix4x4({
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    });
    
    Matrix result = matrixMultiply(A, B);
    REQUIRE(compareMatrix(result, expected) == true);
}

TEST_CASE("A matrix multiplied by a tuple", "[matrix]") {
    Matrix A = matrix4x4({
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    });
    
    Tuple b = point(1, 2, 3);  // tuple(1, 2, 3, 1)
    Tuple expected = point(18, 24, 33);  // tuple(18, 24, 33, 1)
    
    Tuple result = multiply(A, b);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("Multiplying a matrix by the identity matrix", "[matrix]") {
    Matrix A = matrix4x4({
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    });
    
    Matrix I = identity_matrix();
    Matrix result = matrixMultiply(A, I);
    
    REQUIRE(compareMatrix(result, A) == true);
}

TEST_CASE("Multiplying the identity matrix by a tuple", "[matrix]") {
    Tuple a(1, 2, 3, 4);
    Matrix I = identity_matrix();
    
    Tuple result = multiply(I, a);
    
    REQUIRE(equal(result.x, a.x));
    REQUIRE(equal(result.y, a.y));
    REQUIRE(equal(result.z, a.z));
    REQUIRE(equal(result.w, a.w));
}

TEST_CASE("Transposing a matrix", "[matrix]") {
    Matrix A = matrix4x4({
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}
    });
    
    Matrix expected = matrix4x4({
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}
    });
    
    Matrix result = transpose(A);
    REQUIRE(compareMatrix(result, expected) == true);
}

TEST_CASE("Transposing the identity matrix", "[matrix]") {
    Matrix I = identity_matrix();
    Matrix A = transpose(I);
    
    REQUIRE(compareMatrix(A, I) == true);
}

TEST_CASE("Calculating the determinant of a 2x2 matrix", "[matrix]") {
    Matrix A = matrix2x2({
        {1, 5},
        {-3, 2}
    });
    
    REQUIRE(equal(determinant(A), 17));
}

TEST_CASE("A submatrix of a 3x3 matrix is a 2x2 matrix", "[matrix]") {
    Matrix A = matrix3x3({
        {1, 5, 0},
        {-3, 2, 7}, 
        {0, 6, -3}
    });

    Matrix S = matrix2x2({
        {-3, 2}, 
        {0, 6}
    });
    
    REQUIRE(compareMatrix(submatrix(A, 0, 2), S) == true);
}

TEST_CASE("A submatrix of a 4x4 matrix is a 3x3 matrix", "[matrix]") {
    Matrix A = matrix4x4({
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    });

    Matrix S = matrix3x3({
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    });
    
    REQUIRE(compareMatrix(submatrix(A, 2, 1), S) == true);
}

TEST_CASE("Calculating a minor of a 3x3 matrix", "[matrix]") {
    Matrix A = matrix3x3({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    });

    Matrix B = submatrix(A, 1, 0); 
    
    REQUIRE(equal(determinant(B), 25));
    REQUIRE(equal(minor(A, 1, 0), 25));
}

TEST_CASE("Calculating a cofactor of a 3x3 matrix", "[matrix]") {
    Matrix A = matrix3x3({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    });
    
    REQUIRE(equal(minor(A, 0, 0), -12));
    REQUIRE(equal(cofactor(A, 0, 0), -12));
    REQUIRE(equal(minor(A, 1, 0), 25));
    REQUIRE(equal(cofactor(A, 1, 0), -25));
}

TEST_CASE("Calculating the determinant of a 3x3 matrix", "[matrix]") {
    Matrix A = matrix3x3({
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    });
    
    REQUIRE(equal(cofactor(A, 0, 0), 56));
    REQUIRE(equal(cofactor(A, 0, 1), 12));
    REQUIRE(equal(cofactor(A, 0, 2), -46));
    REQUIRE(equal(determinant(A), -196));
}

TEST_CASE("Calculating the determinant of a 4x4 matrix", "[matrix]") {
    Matrix A = matrix4x4({
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    });
    
    REQUIRE(equal(cofactor(A, 0, 0), 690));
    REQUIRE(equal(cofactor(A, 0, 1), 447));
    REQUIRE(equal(cofactor(A, 0, 2), 210));
    REQUIRE(equal(cofactor(A, 0, 3), 51));
    REQUIRE(equal(determinant(A), -4071));
}

TEST_CASE("Testing an invertible matrix for invertibility", "[matrix]") {
    Matrix A = matrix4x4({
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6}
    });
    
    REQUIRE(equal(determinant(A), -2120));
    REQUIRE(is_invertible(A) == true);
}

TEST_CASE("Testing a noninvertible matrix for invertibility", "[matrix]") {
    Matrix A = matrix4x4({
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}
    });
    
    REQUIRE(equal(determinant(A), 0));
    REQUIRE(is_invertible(A) == false);
}

TEST_CASE("Calculating the inverse of a matrix", "[matrix]") {
    Matrix A = matrix4x4({
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    });
    
    REQUIRE(equal(determinant(A), 532));
    REQUIRE(equal(cofactor(A, 2, 3), -160));
    REQUIRE(equal(cofactor(A, 3, 2), 105));
    
    Matrix B = inverse(A);
    
    REQUIRE(equal(B(3, 2), -160.0 / 532.0));
    REQUIRE(equal(B(2, 3), 105.0 / 532.0));
    
    Matrix expected = matrix4x4({
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}
    });
    
    REQUIRE(compareMatrix(B, expected) == true);
}

TEST_CASE("Calculating the inverse of another matrix", "[matrix]") {
    Matrix A = matrix4x4({
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    });
    
    Matrix expected = matrix4x4({
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}
    });
    
    Matrix result = inverse(A);
    REQUIRE(compareMatrix(result, expected) == true);
}

TEST_CASE("Calculating the inverse of a third matrix", "[matrix]") {
    Matrix A = matrix4x4({
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    });
    
    Matrix expected = matrix4x4({
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}
    });
    
    Matrix result = inverse(A);
    REQUIRE(compareMatrix(result, expected) == true);
}

TEST_CASE("Multiplying a product by its inverse", "[matrix]") {
    Matrix A = matrix4x4({
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    });
    
    Matrix B = matrix4x4({
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    });
    
    Matrix C = matrixMultiply(A, B);
    Matrix B_inv = inverse(B);
    Matrix result = matrixMultiply(C, B_inv);
    
    REQUIRE(compareMatrix(result, A) == true);
}

TEST_CASE("Multiplying by a translation matrix", "[matrix]") {
    Matrix transform = translation(5, -3, 2);
    Tuple p = point(-3, 4, 5);
    Tuple expected = point(2, 1, 7);
    
    Tuple result = multiply(transform, p);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("Multiplying by the inverse of a translation matrix", "[matrix]") {
    Matrix transform = translation(5, -3, 2);
    Matrix inv = inverse(transform);
    Tuple p = point(-3, 4, 5);
    Tuple expected = point(-8, 7, 3);
    
    Tuple result = multiply(inv, p);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("Translation does not affect vectors", "[matrix]") {
    Matrix transform = translation(5, -3, 2);
    Tuple v = vector(-3, 4, 5);
    
    Tuple result = multiply(transform, v);
    REQUIRE(equal(result.x, v.x));
    REQUIRE(equal(result.y, v.y));
    REQUIRE(equal(result.z, v.z));
    REQUIRE(equal(result.w, v.w));
}

TEST_CASE("A scaling matrix applied to a point", "[matrix]") {
    Matrix transform = scaling(2, 3, 4);
    Tuple p = point(-4, 6, 8);
    Tuple expected = point(-8, 18, 32);
    
    Tuple result = multiply(transform, p);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("A scaling matrix applied to a vector", "[matrix]") {
    Matrix transform = scaling(2, 3, 4);
    Tuple v = vector(-4, 6, 8);
    Tuple expected = vector(-8, 18, 32);
    
    Tuple result = multiply(transform, v);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("Multiplying by the inverse of a scaling matrix", "[matrix]") {
    Matrix transform = scaling(2, 3, 4);
    Matrix inv = inverse(transform);
    Tuple v = vector(-4, 6, 8);
    Tuple expected = vector(-2, 2, 2);
    
    Tuple result = multiply(inv, v);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("Reflection is scaling by a negative value", "[matrix]") {
    Matrix transform = scaling(-1, 1, 1);
    Tuple p = point(2, 3, 4);
    Tuple expected = point(-2, 3, 4);
    
    Tuple result = multiply(transform, p);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("Rotating a point around the x axis", "[matrix]") {
    Tuple p = point(0, 1, 0);
    Matrix half_quarter = rotation_x(M_PI / 4);
    Matrix full_quarter = rotation_x(M_PI / 2);
    
    Tuple result_half = multiply(half_quarter, p);
    Tuple expected_half = point(0, std::sqrt(2) / 2, std::sqrt(2) / 2);
    REQUIRE(equal(result_half.x, expected_half.x));
    REQUIRE(equal(result_half.y, expected_half.y));
    REQUIRE(equal(result_half.z, expected_half.z));
    REQUIRE(equal(result_half.w, expected_half.w));
    
    Tuple result_full = multiply(full_quarter, p);
    Tuple expected_full = point(0, 0, 1);
    REQUIRE(equal(result_full.x, expected_full.x));
    REQUIRE(equal(result_full.y, expected_full.y));
    REQUIRE(equal(result_full.z, expected_full.z));
    REQUIRE(equal(result_full.w, expected_full.w));
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction", "[matrix]") {
    Tuple p = point(0, 1, 0);
    Matrix half_quarter = rotation_x(M_PI / 4);
    Matrix inv = inverse(half_quarter);
    
    Tuple result = multiply(inv, p);
    Tuple expected = point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    REQUIRE(equal(result.x, expected.x));
    REQUIRE(equal(result.y, expected.y));
    REQUIRE(equal(result.z, expected.z));
    REQUIRE(equal(result.w, expected.w));
}

TEST_CASE("Rotating a point around the y axis", "[matrix]") {
    Tuple p = point(0, 0, 1);
    Matrix half_quarter = rotation_y(M_PI / 4);
    Matrix full_quarter = rotation_y(M_PI / 2);
    
    Tuple result_half = multiply(half_quarter, p);
    Tuple expected_half = point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2);
    REQUIRE(equal(result_half.x, expected_half.x));
    REQUIRE(equal(result_half.y, expected_half.y));
    REQUIRE(equal(result_half.z, expected_half.z));
    REQUIRE(equal(result_half.w, expected_half.w));
    
    Tuple result_full = multiply(full_quarter, p);
    Tuple expected_full = point(1, 0, 0);
    REQUIRE(equal(result_full.x, expected_full.x));
    REQUIRE(equal(result_full.y, expected_full.y));
    REQUIRE(equal(result_full.z, expected_full.z));
    REQUIRE(equal(result_full.w, expected_full.w));
}

TEST_CASE("Rotating a point around the z axis", "[matrix]") {
    Tuple p = point(0, 1, 0);
    Matrix half_quarter = rotation_z(M_PI / 4);
    Matrix full_quarter = rotation_z(M_PI / 2);
    
    Tuple result_half = multiply(half_quarter, p);
    Tuple expected_half = point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
    REQUIRE(equal(result_half.x, expected_half.x));
    REQUIRE(equal(result_half.y, expected_half.y));
    REQUIRE(equal(result_half.z, expected_half.z));
    REQUIRE(equal(result_half.w, expected_half.w));
    
    Tuple result_full = multiply(full_quarter, p);
    Tuple expected_full = point(-1, 0, 0);
    REQUIRE(equal(result_full.x, expected_full.x));
    REQUIRE(equal(result_full.y, expected_full.y));
    REQUIRE(equal(result_full.z, expected_full.z));
    REQUIRE(equal(result_full.w, expected_full.w));
}
