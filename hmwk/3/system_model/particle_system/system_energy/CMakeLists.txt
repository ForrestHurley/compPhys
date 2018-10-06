
cmake_minimum_required(VERSION 2.8)
project(potential_field)

add_subdirectory(potential_energy)
add_subdirectory(tests)

set(POTENTIAL_FIELD_SOURCES src/system_energy.cc src/hamiltonian_energy.cc src/diagonal_hamiltonian_energy.cc src/classical_hamiltonian_energy.cc)

add_library(potential_field ${POTENTIAL_FIELD_SOURCES})

target_include_directories(potential_field PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(potential_field potential_energy)
