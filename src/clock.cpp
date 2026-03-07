// Draws an analog clock face by computing the 12 hour positions using a
// rotation matrix. Clock is centered at origin; we look down the negative
// y-axis, so 12 o'clock is at (0,0,1) and 3 o'clock at (1,0,0).

#include "tuple/tuple.h"
#include "matrix/matrix.h"
#include <cmath>

int main() {
    const int canvas_size = 400;
    const double radius = (3.0 / 8.0) * canvas_size;  // clock radius on canvas
    const double center_x = canvas_size / 2.0;
    const double center_y = canvas_size / 2.0;

    Canvas c = canvas(canvas_size, canvas_size);
    Color white = color(1, 1, 1);

    // Twelve o'clock is at (0, 0, 1) in 3D; we rotate it around the y-axis.
    Tuple twelve = point(0, 0, 1);
    const double radians_per_hour = 2.0 * M_PI / 12.0;  // π/6

    for (int hour = 0; hour < 12; hour++) {
        double angle = hour * radians_per_hour;
        Matrix r = rotation_y(angle);
        Tuple pos = multiply(r, twelve);

        // Map 3D (x, z) to canvas: x → pixel x, z → pixel y.
        // Positive z is "up" (12 o'clock), so subtract from center_y.
        int px = static_cast<int>(std::round(center_x + radius * pos.x));
        int py = static_cast<int>(std::round(center_y - radius * pos.z));

        write_pixel(c, px, py, white);
    }

    save_canvas_to_file(c, "clock.ppm");
    return 0;
}
