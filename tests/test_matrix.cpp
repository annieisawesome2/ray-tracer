#include <catch2/catch_test_macros.hpp>
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
