
cmake_minimum_required(VERSION 2.8)
project(potential_energy_tests)

set(POTENTIAL_ENERGY_TESTS_SOURCES pairwise_potential_energy_test.cc pairwise_potential_energy_test.cc pairwise_potential_function_test.cc pw_brute_test.cc pw_bounded_range_test.cc pw_lattice_grid_test.cc)

add_executable(potential_energy_tests ${POTENTIAL_ENERGY_TESTS_SOURCES})

target_link_libraries(potential_energy_tests gmock_main potential_energy)
