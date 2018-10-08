
cmake_minimum_required(VERSION 2.8)
project(metric_space)

add_subdirectory(tests)

set(METRIC_SPACE_SOURCES src/coordinate.cc src/smooth_coordinate_space.cc src/euclidean_space.cc src/bounded_euclidean_space.cc src/flat_torus_space.cc) 

add_library(metric_space ${METRIC_SPACE_SOURCES})

target_include_directories(metric_space PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
