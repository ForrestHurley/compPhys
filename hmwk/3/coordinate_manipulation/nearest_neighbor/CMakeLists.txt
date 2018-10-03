
project(nearest_neighbor)

set(NEAREST_NEIGHBOR_SOURCES src/fixed_radius_nn.cc src/fr_nn_brute.cc src/fr_nn_cube.cc) 

add_library(nearest_neighbor ${NEAREST_NEIGHBOR_SOURCES})
