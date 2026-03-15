#ifndef RAY_H
#define RAY_H

#include "tuple/tuple.h"

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

Ray ray(const Tuple& origin, const Tuple& direction);
Tuple position(const Ray& r, double t);
Sphere sphere();
std::vector<double> intersect(const Sphere& sphere, const Ray& ray);

#endif // RAY_H
