
cmake_minimum_required(VERSION 2.8)
project(system_energy)

add_subdirectory(potential_energy)
add_subdirectory(tests)

set(SYSTEM_ENERGY_SOURCES src/system_energy.cc src/hamiltonian_energy.cc src/diagonal_hamiltonian_energy.cc src/classical_hamiltonian_energy.cc)

add_library(system_energy ${SYSTEM_ENERGY_SOURCES})

target_include_directories(system_energy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(system_energy potential_energy particle_state)
