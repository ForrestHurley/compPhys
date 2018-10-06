
cmake_minimum_required(VERSION 2.8)
project(particle_state)

add_subdirectory(tests)

set(PARTICLE_STATE_SOURCES src/particle_state.cc src/hamiltonian_particle_state.cc)

add_library(particle_state ${PARTICLE_STATE_SOURCES})

target_include_directories(particle_state ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(particle_state coordinate_manipulation)
