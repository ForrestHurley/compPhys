
cmake_minimum_required(VERSION 2.8)
project(particle_state_tests)

set(PARTICLE_STATE_TESTS_SOURCES particle_state_test.cc hamiltonian_particle_state_test.cc)

add_executable(particle_state_tests ${PARTICLE_STATE_TESTS_SOURCES})

target_link_libraries(particle_state_tests gmock_main particle_state)
