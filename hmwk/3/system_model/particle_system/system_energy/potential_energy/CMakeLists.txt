
cmake_minimum_required(VERSION 2.8)
project(potential_energy)

add_subdirectory(tests)

set(POTENTIAL_ENERGY_SOURCES src/potential_energy.cc src/pairwise_potential_energy.cc src/pw_brute.cc src/pw_bounded_range.cc src/pw_lattice_grid.cc)

add_library(potential_energy ${POTENTIAL_ENERGY_SOURCES})
target_include_directories(potential_energy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(potential_energy metric_space nearest_neighbor)
