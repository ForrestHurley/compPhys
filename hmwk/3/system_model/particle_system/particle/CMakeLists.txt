
cmake_minimum_required(VERSION 2.8)

project(particle)

subdirs(tests)

set(PARTICLE_SOURCES src/particle_state.cc src/particle_potential.cc)

add_library(particle ${PARTICLE_SOURCES})

target_include_directories(particle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
