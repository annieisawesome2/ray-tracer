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

TEST_CASE("Matrix equality with identical matrices", "[matrix]") {
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
    
    REQUIRE(A == B);
}

TEST_CASE("Matrix equality with different matrices", "[matrix]") {
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
    
    REQUIRE(A != B);
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

