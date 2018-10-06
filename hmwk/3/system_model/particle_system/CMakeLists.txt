
cmake_minimum_required(VERSION 2.8)
project(particle_system)

add_subdirectory(system_energy)
add_subdirectory(particle_state)
add_subdirectory(tests)

set(PARTICLE_SYSTEM_SOURCE src/particle_system.cc src/hamiltonian_particle_system.cc src/classical_particle_system.cc src/classical_pairwise_particle_system.cc)

add_library(particle_system ${PARTICLE_SYSTEM_SOURCE})

target_include_directories(particle_system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(particle_system particle_state system_energy)
