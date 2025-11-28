#include <catch2/catch_test_macros.hpp>
#include "tuple.h"

TEST_CASE("A tuple with w=1.0 is a point", "[tuple]") {
    Tuple a(4.3, -4.2, 3.1, 1.0);
    
    REQUIRE(equal(a.x, 4.3));
    REQUIRE(equal(a.y, -4.2));
    REQUIRE(equal(a.z, 3.1));
    REQUIRE(equal(a.w, 1.0));
    REQUIRE(a.is_point() == true);
    REQUIRE(a.is_vector() == false);
}

TEST_CASE("A tuple with w=0 is a vector", "[tuple]") {
    Tuple a(4.3, -4.2, 3.1, 0.0);
    
    REQUIRE(equal(a.x, 4.3));
    REQUIRE(equal(a.y, -4.2));
    REQUIRE(equal(a.z, 3.1));
    REQUIRE(equal(a.w, 0.0));
    REQUIRE(a.is_point() == false);
    REQUIRE(a.is_vector() == true);
}

TEST_CASE("point() creates tuples with w=1", "[tuple]") {
    Tuple p = point(4, -4, 3);
    Tuple expected(4, -4, 3, 1);
    
    REQUIRE(p == expected);
    REQUIRE(p.is_point() == true);
    REQUIRE(p.is_vector() == false);
}

TEST_CASE("vector() creates tuples with w=0", "[tuple]") {
    Tuple v = vector(4, -4, 3);
    Tuple expected(4, -4, 3, 0);
    
    REQUIRE(v == expected);
    REQUIRE(v.is_point() == false);
    REQUIRE(v.is_vector() == true);
}

TEST_CASE("Floating point comparison with EPSILON", "[tuple]") {
    REQUIRE(equal(0.0, 0.0) == true);
    REQUIRE(equal(1.0, 1.0) == true);
    REQUIRE(equal(0.000001, 0.000002) == true);  // Within EPSILON
    REQUIRE(equal(0.00001, 0.00002) == true);    // Within EPSILON
    REQUIRE(equal(0.0001, 0.0002) == false);     // Outside EPSILON
    REQUIRE(equal(1.0, 2.0) == false);
}

