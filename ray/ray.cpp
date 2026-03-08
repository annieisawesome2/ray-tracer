#include "ray.h"

Ray ray(const Tuple& origin, const Tuple& direction) {
    return Ray(origin, direction);
}

Tuple position(const Ray& r, double t) {
    Tuple scaled = r.direction;
    multiply(scaled, t);
    return add(r.origin, scaled);
}