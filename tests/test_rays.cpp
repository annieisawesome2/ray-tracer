#include "ray/ray.h"
#include "tuple/tuple.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Creating and querying a ray", "[ray]") {
    Tuple origin = point(1, 2, 3);
    Tuple direction = vector(4, 5, 6);
    Ray r = ray(origin, direction);

    REQUIRE(r.origin == origin);
    REQUIRE(r.direction == direction);
}
