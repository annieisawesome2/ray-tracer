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

Ray transform(const Ray& r, const Matrix& m) {
    return Ray(multiply(m, r.origin), multiply(m, r.direction));
}

Sphere sphere() {
    return Sphere(point(0, 0, 0), 1.0, identity_matrix());
}

void set_transform(Sphere& s, const Matrix& transform) {
    s.transform = transform;
}

Intersection intersection(double t, const Sphere& object) {
    return Intersection(t, object);
}

Intersections intersections(std::initializer_list<Intersection> xs) {
    Intersections result;
    result.hits.assign(xs.begin(), xs.end());
    std::sort(result.hits.begin(), result.hits.end(),
        [](const Intersection& a, const Intersection& b) { return a.t < b.t; });
    return result;
}

Intersections intersect(const Sphere& sphere, const Ray& ray) {
    Ray ray2 = transform(ray, inverse(sphere.transform));

    // Ray-sphere intersection solves the quadratic:
    //   a*t^2 + b*t + c = 0
    // where p(t) = ray.origin + t*ray.direction
    Tuple sphere_to_ray = subtract(ray2.origin, sphere.origin);

    double a = dot(ray2.direction, ray2.direction);
    double b = 2.0 * dot(ray2.direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - (sphere.radius * sphere.radius);

    double discriminant = (b * b) - (4.0 * a * c);
    Intersections xs;

    if (discriminant < 0.0) {
        return xs;
    }

    double sqrt_disc = std::sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2.0 * a);
    double t2 = (-b + sqrt_disc) / (2.0 * a);

    xs.hits.push_back(intersection(t1, sphere));
    xs.hits.push_back(intersection(t2, sphere));

    if (xs.hits[0].t > xs.hits[1].t) {
        std::swap(xs.hits[0], xs.hits[1]);
    }
    return xs;
}

std::optional<Intersection> hit(const Intersections& xs) {
    std::optional<Intersection> lowest;
    for (const auto& i : xs.hits) {
        if (i.t < 0) {
            continue;
        }
        if (!lowest.has_value() || i.t < lowest->t) {
            lowest = i;
        }
    }
    return lowest;
}

