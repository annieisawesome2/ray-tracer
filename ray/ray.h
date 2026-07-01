#ifndef RAY_H
#define RAY_H

#include "tuple/tuple.h"
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

    Sphere(const Tuple& origin, double radius)
        : origin(origin), radius(radius) {}
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
Sphere sphere();
Intersection intersection(double t, const Sphere& object);
Intersections intersections(std::initializer_list<Intersection> xs);
Intersections intersect(const Sphere& sphere, const Ray& ray);
std::optional<Intersection> hit(const Intersections& xs);

#endif // RAY_H
