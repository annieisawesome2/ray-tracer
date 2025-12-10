cmake_minimum_required(VERSION 3.14)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.0
)
FetchContent_MakeAvailable(Catch2)

# Source files
set(SOURCES
    src/tuple.cpp
)

# Create library
add_library(ray_tracer_lib ${SOURCES})

# Test executable
enable_testing()
add_executable(tests tests/test_tuple.cpp)
target_link_libraries(tests ray_tracer_lib Catch2::Catch2WithMain)

# Add test
add_test(NAME TupleTests COMMAND tests)

# Projectile visualization executable
add_executable(projectile src/projectile.cpp)
target_link_libraries(projectile ray_tracer_lib)

