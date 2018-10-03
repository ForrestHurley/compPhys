
project(metric_space)

set(METRIC_SPACE_SOURCES src/metric_space.cc src/coordinate.cc src/euclidean_space.cc src/bounded_euclidean_space.cc src/flat_torus_space.cc) 

add_library(metric_space ${METRIC_SPACE_SOURCES})
