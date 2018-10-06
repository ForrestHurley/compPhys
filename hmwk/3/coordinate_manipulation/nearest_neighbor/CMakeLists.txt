
cmake_minimum_required(VERSION 2.8)
project(nearest_neighbor)

add_subdirectory(tests)

set(NEAREST_NEIGHBOR_SOURCES src/fixed_radius_nn.cc src/fr_nn_brute.cc src/fr_nn_cube.cc) 

add_library(nearest_neighbor ${NEAREST_NEIGHBOR_SOURCES})

target_include_directories(nearest_neighbor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(nearest_neighbor metric_space)
