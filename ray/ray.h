#ifndef RAY_H
#define RAY_H

#include "tuple/tuple.h"

struct Ray {
    Tuple origin;
    Tuple direction;

    Ray(const Tuple& origin, const Tuple& direction)
        : origin(origin), direction(direction) {}
};

Ray ray(const Tuple& origin, const Tuple& direction);

#endif // RAY_H
