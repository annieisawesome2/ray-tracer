#include "ray/ray.h"
#include "tuple/tuple.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Creating and querying a ray", "[ray]") {
    Tuple origin = point(1, 2, 3);
    Tuple direction = vector(4, 5, 6);
    Ray r = ray(origin, direction);

    REQUIRE(r.origin == origin);
    REQUIRE(r.direction == direction);
}


TEST_CASE("Computing a point from a distance", "[ray]") {
    Tuple p1 = point(2, 3, 4);
    Tuple p2 = point(3, 3, 4);
    Tuple p3 = point(1, 3, 4);
    Tuple p4 = point(4.5, 3, 4);
    Tuple v = vector(1, 0, 0); 
    Ray r = ray(p1, v);


    REQUIRE(position(r, 0) == p1);
    REQUIRE(position(r, 1) == p2);
    REQUIRE(position(r, -1) == p3);
    REQUIRE(position(r, 2.5) == p4);
}

TEST_CASE("Ray intersects sphere at two points", "[ray]") {
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    std::vector<double> xs = intersect(s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(equal(xs[0], 4.0));
    REQUIRE(equal(xs[1], 6.0));
}