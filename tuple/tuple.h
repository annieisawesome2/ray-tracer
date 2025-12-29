#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>
#include <vector>
#include <string>

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
    Color(double red = 0.0, double green = 0.0, double blue = 0.0)
        : Tuple(red, green, blue, 0.0) {}

    // Accessors that return references to x, y, z as red, green, blue
    double& red() { return x; }
    double& green() { return y; }
    double& blue() { return z; }
    
    const double& red() const { return x; }
    const double& green() const { return y; }
    const double& blue() const { return z; }
};

// Canvas class for storing pixels
class Canvas {
public:
    int width;
    int height;
    std::vector<std::vector<Color>> pixels;

    Canvas(int width, int height)
        : width(width), height(height), pixels(height, std::vector<Color>(width, Color(0, 0, 0))) {}
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
Color blend(const Color& c1, const Color& c2);

// Canvas functions
Canvas canvas(int width, int height);
void write_pixel(Canvas& c, int x, int y, const Color& color);
Color pixel_at(const Canvas& c, int x, int y);
std::string canvas_to_ppm(const Canvas& c);
void save_canvas_to_file(const Canvas& c, const std::string& filename); 

#endif // TUPLE_H

