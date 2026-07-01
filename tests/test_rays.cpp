#include "ray/ray.h"
#include "tuple/tuple.h"
#include <catch2/catch_test_macros.hpp>

static bool same_sphere(const Sphere& a, const Sphere& b) {
    return a.origin == b.origin && equal(a.radius, b.radius);
}

static bool same_intersection(const Intersection& a, const Intersection& b) {
    return equal(a.t, b.t) && same_sphere(a.object, b.object);
}

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
    Intersections xs = intersect(s, r);
    REQUIRE(xs.size() == 2);
    REQUIRE(equal(xs[0].t, 4.0));
    REQUIRE(equal(xs[1].t, 6.0));
}

TEST_CASE("Ray intersects sphere at a tangent", "[ray]") {
    Ray r = ray(point(0, 1, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersections xs = intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(equal(xs[0].t, 5.0));
    REQUIRE(equal(xs[1].t, 5.0));
}

TEST_CASE("Ray misses sphere", "[ray]") {
    Ray r = ray(point(0, 2, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersections xs = intersect(s, r);

    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere", "[ray]") {
    Ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    Sphere s = sphere();
    Intersections xs = intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(equal(xs[0].t, -1.0));
    REQUIRE(equal(xs[1].t, 1.0));
}

TEST_CASE("A sphere is behind a ray", "[ray]") {
    Ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersections xs = intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(equal(xs[0].t, -6.0));
    REQUIRE(equal(xs[1].t, -4.0));
}

TEST_CASE("An intersection encapsulates t and object", "[intersections]") {
    Sphere s = sphere();
    Intersection i = intersection(3.5, s);

    REQUIRE(equal(i.t, 3.5));
    REQUIRE(same_sphere(i.object, s));
}

TEST_CASE("Aggregating intersections", "[intersections]") {
    Sphere s = sphere();
    Intersection i1 = intersection(1, s);
    Intersection i2 = intersection(2, s);
    Intersections xs = intersections({i1, i2});

    REQUIRE(xs.size() == 2);
    REQUIRE(equal(xs[0].t, 1.0));
    REQUIRE(equal(xs[1].t, 2.0));
}

TEST_CASE("Intersect sets the object on the intersection", "[ray]") {
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    Intersections xs = intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(same_sphere(xs[0].object, s));
    REQUIRE(same_sphere(xs[1].object, s));
}

TEST_CASE("The hit, when all intersections have positive t", "[intersections]") {
    Sphere s = sphere();
    Intersection i1 = intersection(1, s);
    Intersection i2 = intersection(2, s);
    Intersections xs = intersections({i2, i1});
    std::optional<Intersection> i = hit(xs);

    REQUIRE(i.has_value());
    REQUIRE(same_intersection(*i, i1));
}

TEST_CASE("The hit, when some intersections have negative t", "[intersections]") {
    Sphere s = sphere();
    Intersection i1 = intersection(-1, s);
    Intersection i2 = intersection(1, s);
    Intersections xs = intersections({i2, i1});
    std::optional<Intersection> i = hit(xs);

    REQUIRE(i.has_value());
    REQUIRE(same_intersection(*i, i2));
}

TEST_CASE("The hit, when all intersections have negative t", "[intersections]") {
    Sphere s = sphere();
    Intersection i1 = intersection(-2, s);
    Intersection i2 = intersection(-1, s);
    Intersections xs = intersections({i2, i1});
    std::optional<Intersection> i = hit(xs);

    REQUIRE(!i.has_value());
}

TEST_CASE("The hit is always the lowest nonnegative intersection", "[intersections]") {
    Sphere s = sphere();
    Intersection i1 = intersection(5, s);
    Intersection i2 = intersection(7, s);
    Intersection i3 = intersection(-3, s);
    Intersection i4 = intersection(2, s);
    Intersections xs = intersections({i1, i2, i3, i4});
    std::optional<Intersection> i = hit(xs);

    REQUIRE(i.has_value());
    REQUIRE(same_intersection(*i, i4));
}

