
cmake_minimum_required(VERSION 2.8)
project(system_update_tests)

set(SYSTEM_UPDATE_TESTS_SOURCES basic_update_test.cc dynamics_update_test.cc metropolis_update_test.cc metropolis_dynamics_update_test.cc)

add_executable(system_update_tests ${SYSTEM_UPDATE_TESTS_SOURCES})

target_link_libraries(system_update_tests gmock_main system_update)
