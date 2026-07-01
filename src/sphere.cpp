#include "tuple/tuple.h"
#include "ray/ray.h"
#include <iostream>

int main() {
    const int canvas_pixels = 100;
    const double wall_z = 10.0;
    const double wall_size = 7.0;
    const double pixel_size = wall_size / canvas_pixels;
    const double half = wall_size / 2.0;
    const Tuple ray_origin = point(0, 0, -5);

    Canvas c = canvas(canvas_pixels, canvas_pixels);
    Color red = color(1, 0, 0);
    Sphere shape = sphere();

    for (int y = 0; y < canvas_pixels; y++) {
        double world_y = half - pixel_size * y;
        for (int x = 0; x < canvas_pixels; x++) {
            double world_x = -half + pixel_size * x;
            Tuple position = point(world_x, world_y, wall_z);
            Ray r = ray(ray_origin, normalize(subtract(position, ray_origin)));
            Intersections xs = intersect(shape, r);

            if (hit(xs).has_value()) {
                write_pixel(c, x, y, red);
            }
        }
    }

    save_canvas_to_file(c, "sphere.ppm");
    std::cout << "Canvas saved to sphere.ppm" << std::endl;
    std::cout << "To view on Mac, run: open sphere.ppm" << std::endl;

    return 0;
}
