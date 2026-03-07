# Ray Tracer Challenge

A test-driven implementation of a 3D ray tracer in C++.

## Project structure

- **tuple/** — Points, vectors, colors, and canvas (PPM output)
- **matrix/** — 4×4 matrices, transforms (translation, scaling, rotation, etc.)
- **src/** — Executables: projectile simulation and clock face
- **tests/** — Catch2 unit tests for tuple and matrix

## Building

Requirements:
- CMake 3.14 or higher
- C++17 compiler
- Catch2 is fetched automatically via CMake FetchContent

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running tests

```bash
./build/tests
```

## Executables

### Clock face

Draws 12 hour positions on an analog clock using a y-axis rotation matrix. The clock is centered at the origin; the view is along the negative y-axis (12 o'clock at (0,0,1), 3 o'clock at (1,0,0)). Writes a PPM image with one white pixel per hour.

```bash
cmake --build build --target clock
./build/clock
open clock.ppm    # open the image (e.g. in Preview on Mac)
```

Output: `clock.ppm` (created in the project root when you run `./build/clock` from there).

### Projectile

Simulates a projectile under gravity and wind, plotting its path to a canvas.

```bash
cmake --build build --target projectile
./build/projectile
open projectile.ppm
```

Output: `projectile.ppm`