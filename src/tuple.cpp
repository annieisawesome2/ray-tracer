#include "tuple.h"

Tuple point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
}

Tuple vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
}

bool equal(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

