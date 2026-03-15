#include "ray.h"

Ray ray(const Tuple& origin, const Tuple& direction) {
    return Ray(origin, direction);
}

Tuple position(const Ray& r, double t) {
    Tuple scaled = r.direction;
    multiply(scaled, t);
    return add(r.origin, scaled);
}

Sphere sphere() {
    return Sphere(point(0, 0, 0), 1.0); 
}

std::vector<double> intersect(const Sphere& sphere, const Ray& ray) {
    std::vector<double> xs;
    return xs;
}

