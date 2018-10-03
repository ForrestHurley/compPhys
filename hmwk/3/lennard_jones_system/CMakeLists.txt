
cmake_minimum_required(VERSION 2.8)

project(lennard_jones)

set(LENNARD_JONES_SOURCE src/simulate_system.cc src/lennard_jones_potential.cc)

add_executable(lennard_jones ${LENNARD_JONES_SOURCE})

target_include_directories(lennard_jones PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lennard_jones system_model)
