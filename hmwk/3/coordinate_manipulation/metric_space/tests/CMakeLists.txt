
cmake_minimum_required(VERSION 2.8)
project(metric_space_tests)

set(METRIC_SPACE_TESTS_SOURCES coordinate_test.cc euclidean_space_test.cc bounded_euclidean_space_test.cc flat_torus_space_test.cc)

add_executable(metric_space_tests ${METRIC_SPACE_TESTS_SOURCES})

target_link_libraries(metric_space_tests gmock_main metric_space)
