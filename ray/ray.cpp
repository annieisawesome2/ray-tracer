#include "ray.h"
#include <cmath>
#include <algorithm>

Ray ray(const Tuple& origin, const Tuple& direction) {
    return Ray(origin, direction);
}

Tuple position(const Ray& r, double t) {
    Tuple scaled = r.direction;
    multiply(scaled, t);
    return add(r.origin, scaled);
}

Sphere sphere() {
    return Sphere(point(0, 0, 0), 1.0); 
}

std::vector<double> intersect(const Sphere& sphere, const Ray& ray) {
    // Ray-sphere intersection solves the quadratic:
    //   a*t^2 + b*t + c = 0
    // where p(t) = ray.origin + t*ray.direction
    Tuple sphere_to_ray = subtract(ray.origin, sphere.origin);

    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(ray.direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - (sphere.radius * sphere.radius);

    double discriminant = (b * b) - (4.0 * a * c);
    std::vector<double> xs;

    if (discriminant < 0.0) {
        return xs;
    }

    double sqrt_disc = std::sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2.0 * a);
    double t2 = (-b + sqrt_disc) / (2.0 * a);

    xs.push_back(t1);
    if (!equal(t1, t2)) {
        xs.push_back(t2);
    }

    if (xs.size() == 2 && xs[0] > xs[1]) {
        std::swap(xs[0], xs[1]);
    }

    return xs;
}

