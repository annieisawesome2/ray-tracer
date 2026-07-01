#ifndef RAY_H
#define RAY_H

#include "tuple/tuple.h"
#include "matrix/matrix.h"
#include <vector>
#include <initializer_list>
#include <optional>

struct Ray {
    Tuple origin;
    Tuple direction;

    Ray(const Tuple& origin, const Tuple& direction)
        : origin(origin), direction(direction) {}
};

struct Sphere {
    Tuple origin;
    double radius;
    Matrix transform;

    Sphere(const Tuple& origin, double radius, const Matrix& transform)
        : origin(origin), radius(radius), transform(transform) {}
};

struct Intersection {
    double t;
    Sphere object;

    Intersection(double t, const Sphere& object)
        : t(t), object(object) {}
};

struct Intersections {
    std::vector<Intersection> hits;

    size_t size() const { return hits.size(); }
    const Intersection& operator[](size_t i) const { return hits[i]; }
};

Ray ray(const Tuple& origin, const Tuple& direction);
Tuple position(const Ray& r, double t);
Ray transform(const Ray& r, const Matrix& m);
Sphere sphere();
void set_transform(Sphere& s, const Matrix& transform);
Intersection intersection(double t, const Sphere& object);
Intersections intersections(std::initializer_list<Intersection> xs);
Intersections intersect(const Sphere& sphere, const Ray& ray);
std::optional<Intersection> hit(const Intersections& xs);

#endif // RAY_H
