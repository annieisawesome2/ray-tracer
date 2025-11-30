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

TEST_CASE("equal() function compares two tuples", "[tuple]") {
    Tuple a(4.3, -4.2, 3.1, 1.0);
    Tuple b(4.3, -4.2, 3.1, 1.0);
    Tuple c(4.3, -4.2, 3.1, 0.0);
    Tuple d(1.0, 2.0, 3.0, 1.0);
    
    REQUIRE(equal(a, b) == true);
    REQUIRE(equal(a, c) == false);
    REQUIRE(equal(a, d) == false);
    REQUIRE(equal(c, d) == false);
    
    // Test with small floating point differences
    Tuple e(4.3, -4.2, 3.1, 1.0);
    Tuple f(4.300001, -4.200001, 3.100001, 1.000001);
    REQUIRE(equal(e, f) == true);  // Within EPSILON
    
    Tuple g(4.3, -4.2, 3.1, 1.0);
    Tuple h(4.3001, -4.2001, 3.1001, 1.0001);
    REQUIRE(equal(g, h) == false);  // Outside EPSILON
}

TEST_CASE("adding tuples", "[tuple]") {
    Tuple a1(3, -2, 5, 1); 
    Tuple a2(-2, 3, 1, 0);
    Tuple a3(1, 1, 6, 1);

    REQUIRE(add(a1, a2) == a3);
}

TEST_CASE("subtracting tuples", "[tuple]") {
    Tuple p1(3, 2, 1, 1); 
    Tuple p2(5, 6, 7, 1);
    Tuple v1(-2, -4, -6, 0);

    REQUIRE(subtract(p1, p2) == v1);

    Tuple p(3, 2, 1, 1); 
    Tuple v(5, 6, 7, 0);
    Tuple p4(-2, -4, -6, 1);

    REQUIRE(subtract(p, v) == p4);
}

TEST_CASE("negating tuples", "[tuple]") {
    Tuple v1(1, -2, 3, 0);
    Tuple v2(-1, 2, -3, 0);

    REQUIRE(negate(v1) == v2);
}

