#include "tuple.h"
#include <sstream>
#include <algorithm>

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

Color blend(const Color& c1, const Color& c2) {
    // Hadamard product
    double r = c1.red() * c2.red(); 
    double g = c1.green() * c2.green(); 
    double b = c1.blue() * c2.blue(); 

    Color result(r, g, b); 
    return result; 
}

// Canvas functions
Canvas canvas(int width, int height) {
    return Canvas(width, height);
}

void write_pixel(Canvas& c, int x, int y, const Color& color) {
    if (x >= 0 && x < c.width && y >= 0 && y < c.height) {
        c.pixels[y][x] = color;
    }
}

Color pixel_at(const Canvas& c, int x, int y) {
    if (x >= 0 && x < c.width && y >= 0 && y < c.height) {
        return c.pixels[y][x];
    }
    return color(0, 0, 0); // Return black for out-of-bounds
}

std::string canvas_to_ppm(const Canvas& c) {
    std::ostringstream ppm;
    
    // Header
    ppm << "P3\n";
    ppm << c.width << " " << c.height << "\n";
    ppm << "255\n";
    
    // Pixel data with line length limit (70 characters)
    const int MAX_LINE_LENGTH = 70;
    std::string current_line;
    
    for (int y = 0; y < c.height; y++) {
        for (int x = 0; x < c.width; x++) {
            const Color& pixel = c.pixels[y][x];
            
            // Scale and clamp color values to 0-255
            int r = static_cast<int>(std::round(std::max(0.0, std::min(1.0, pixel.red())) * 255.0));
            int g = static_cast<int>(std::round(std::max(0.0, std::min(1.0, pixel.green())) * 255.0));
            int b = static_cast<int>(std::round(std::max(0.0, std::min(1.0, pixel.blue())) * 255.0));
            
            // Format the RGB values as individual components
            std::ostringstream r_str, g_str, b_str;
            r_str << r;
            g_str << g;
            b_str << b;
            std::string r_val = r_str.str();
            std::string g_val = g_str.str();
            std::string b_val = b_str.str();
            
            // Add each component, checking line length
            // Add red component
            if (!current_line.empty()) {
                if (current_line.length() + 1 + r_val.length() > MAX_LINE_LENGTH) {
                    ppm << current_line << "\n";
                    current_line = r_val;
                } else {
                    current_line += " " + r_val;
                }
            } else {
                current_line = r_val;
            }
            
            // Add green component
            if (current_line.length() + 1 + g_val.length() > MAX_LINE_LENGTH) {
                ppm << current_line << "\n";
                current_line = g_val;
            } else {
                current_line += " " + g_val;
            }
            
            // Add blue component
            if (current_line.length() + 1 + b_val.length() > MAX_LINE_LENGTH) {
                ppm << current_line << "\n";
                current_line = b_val;
            } else {
                current_line += " " + b_val;
            }
        }
        
        // End of row - output current line and start new line
        if (!current_line.empty()) {
            ppm << current_line << "\n";
            current_line.clear();
        }
    }
    
    // Ensure file ends with newline (if current_line is empty, we already have a newline from last row)
    // But we need to make sure there's always a trailing newline
    return ppm.str();
}