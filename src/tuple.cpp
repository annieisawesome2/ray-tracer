#include "tuple.h"

Tuple point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
}

Tuple vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
}

Color color(double red, double green, double blue) {
    return Color(red, green, blue);
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

Tuple negate(Tuple& a) { 
    a.x = -a.x; 
    a.y = -a.y; 
    a.z = -a.z; 
    a.w = -a.w; 

    return a; 
} 

Tuple multiply(Tuple&a, double scale) {
    a.x *= scale; 
    a.y *= scale; 
    a.z *= scale; 
    a.w *= scale; 

    return a; 
}

double magnitude(const Tuple& a) {
    return std::sqrt(std::pow(a.x, 2.0) + std::pow(a.y, 2.0) + std::pow(a.z, 2.0) + std::pow(a.w, 2.0));
}

Tuple normalize(const Tuple& a) {
    double mag = magnitude(a);
    return Tuple(a.x / mag, a.y / mag, a.z / mag, a.w / mag);
}

double dot(const Tuple&a, const Tuple& b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

Tuple cross(const Tuple&a, const Tuple& b) {
    Tuple v = vector((a.y * b.z) - (a.z * b.y), 
                     (a.z * b.x) - (a.x * b.z),
                     (a.x * b.y) - (a.y * b.x));
    return v; 
}