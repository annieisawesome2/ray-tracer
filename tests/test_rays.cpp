#include "ray/ray.h"
#include "tuple/tuple.h"
#include "matrix/matrix.h"
#include <catch2/catch_test_macros.hpp>
#include <cmath>

static bool same_sphere(const Sphere& a, const Sphere& b) {
    return a.origin == b.origin &&
           equal(a.radius, b.radius) &&
           compareMatrix(a.transform, b.transform);
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

TEST_CASE("Translating a ray", "[ray]") {
    Ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    Matrix m = translation(3, 4, 5);
    Ray r2 = transform(r, m);

    REQUIRE(r2.origin == point(4, 6, 8));
    REQUIRE(r2.direction == vector(0, 1, 0));
    REQUIRE(r.origin == point(1, 2, 3));
    REQUIRE(r.direction == vector(0, 1, 0));
}


TEST_CASE("Scaling a ray", "[ray]") {
    Ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    Matrix m = scaling(2, 3, 4);
    Ray r2 = transform(r, m);

    REQUIRE(r2.origin == point(2, 6, 12));
    REQUIRE(r2.direction == vector(0, 3, 0));
}

TEST_CASE("A sphere's default transformation", "[sphere]") {
    Sphere s = sphere();
    REQUIRE(compareMatrix(s.transform, identity_matrix()));
}

TEST_CASE("Changing a sphere's transformation", "[sphere]") {
    Sphere s = sphere();
    Matrix t = translation(2, 3, 4);
    set_transform(s, t);
    REQUIRE(compareMatrix(s.transform, t));
}

TEST_CASE("Intersecting a scaled sphere with a ray", "[sphere]") {
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    set_transform(s, scaling(2, 2, 2));
    Intersections xs = intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(equal(xs[0].t, 3.0));
    REQUIRE(equal(xs[1].t, 7.0));
}

TEST_CASE("Intersecting a translated sphere with a ray", "[sphere]") {
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();
    set_transform(s, translation(5, 0, 0));
    Intersections xs = intersect(s, r);

    REQUIRE(xs.size() == 0);
}

TEST_CASE("The normal on a sphere on the x axis", "[sphere]") { 
    Sphere s = sphere(); 
    Tuple n = normal_at(s, point(1, 0, 0)); 
    REQUIRE(n == vector(1, 0, 0));
}

TEST_CASE("The normal on a sphere on the y axis", "[sphere]") { 
    Sphere s = sphere(); 
    Tuple n = normal_at(s, point(0, 1, 0)); 
    REQUIRE(n == vector(0, 1, 0));
}

TEST_CASE("The normal on a sphere on the z axis", "[sphere]") {
    Sphere s = sphere();
    Tuple n = normal_at(s, point(0, 0, 1));
    REQUIRE(n == vector(0, 0, 1));
}

TEST_CASE("The normal on a sphere at a nonaxial point", "[sphere]") {
    Sphere s = sphere();
    double v = std::sqrt(3.0) / 3.0;
    Tuple n = normal_at(s, point(v, v, v));
    REQUIRE(n == vector(v, v, v));
}

TEST_CASE("The normal is a normalized vector", "[sphere]") {
    Sphere s = sphere();
    double v = std::sqrt(3.0) / 3.0;
    Tuple n = normal_at(s, point(v, v, v));
    REQUIRE(n == normalize(n));
}

TEST_CASE("Computing the normal on a translated sphere", "[sphere]") {
    Sphere s = sphere();
    set_transform(s, translation(0, 1, 0));
    Tuple n = normal_at(s, point(0, 1.70711, -0.70711));
    REQUIRE(n == vector(0, 0.70711, -0.70711));
}

TEST_CASE("Computing the normal on a transformed sphere", "[sphere]") {
    Sphere s = sphere();
    Matrix m = matrixMultiply(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
    set_transform(s, m);
    double v = std::sqrt(2.0) / 2.0;
    Tuple n = normal_at(s, point(0, v, -v));
    REQUIRE(n == vector(0, 0.97014, -0.24254));
}