#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>

constexpr double EPSILON = 0.00001;

class Tuple {
public:
    double x, y, z, w;

    Tuple(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0)
        : x(x), y(y), z(z), w(w) {}

    bool is_point() const {
        return std::abs(w - 1.0) < EPSILON;
    }

    bool is_vector() const {
        return std::abs(w - 0.0) < EPSILON;
    }

    bool operator==(const Tuple& other) const {
        return std::abs(x - other.x) < EPSILON &&
               std::abs(y - other.y) < EPSILON &&
               std::abs(z - other.z) < EPSILON &&
               std::abs(w - other.w) < EPSILON;
    }

    bool operator!=(const Tuple& other) const {
        return !(*this == other);
    }
};

// Color class built on top of Tuple
class Color : public Tuple {
public:
    // References to x, y, z as red, green, blue
    double& red;
    double& green;
    double& blue;

    Color(double red = 0.0, double green = 0.0, double blue = 0.0)
        : Tuple(red, green, blue, 0.0), red(x), green(y), blue(z) {}
};

// Factory functions
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);
Color color(double red, double green, double blue);

// Floating point comparison utility
bool equal(double a, double b);

// Tuple comparison function
bool equal(const Tuple& a, const Tuple& b);

// Tuple Operations
Tuple add(const Tuple& a, const Tuple& b); 
Tuple subtract(const Tuple& a, const Tuple& b); 
Tuple negate(Tuple& a); 
Tuple multiply(Tuple& a, double scale); 
double magnitude(const Tuple& a); 
Tuple normalize(const Tuple& a); 
double dot(const Tuple&a, const Tuple& b); 
Tuple cross(const Tuple&a, const Tuple& b); 

#endif // TUPLE_H

