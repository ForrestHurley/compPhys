
cmake_minimum_required(VERSION 2.8)
project(particle_system)

add_subdirectory(potential_field)
add_subdirectory(particle)

set(PARTICLE_SYSTEM_SOURCE src/particle_system.cc)

add_library(particle_system ${PARTICLE_SYSTEM_SOURCE})

target_link_libraries(particle_system potential_field particle)
