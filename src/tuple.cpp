#include "tuple.h"

Tuple point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
}

Tuple vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
}

bool equal(double a, double b) {
    return std::abs(a - b) <= EPSILON;
}

bool equal(const Tuple& a, const Tuple& b) {
    return std::abs(a.x - b.x) < EPSILON &&
           std::abs(a.y - b.y) < EPSILON &&
           std::abs(a.z - b.z) < EPSILON &&
           std::abs(a.w - b.w) < EPSILON;
}

Tuple add(const Tuple& a, const Tuple& b) {
    // point + vector = point
    // point + point is not valid
    Tuple tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); 
    return tuple; 
}

Tuple subtract(const Tuple& a, const Tuple& b) {
    Tuple tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); 
    return tuple; 
}

