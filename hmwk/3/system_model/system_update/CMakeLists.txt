
cmake_minimum_required(VERSION 2.8)
project(system_update)

add_subdirectory(tests)

set(SYSTEM_UPDATE_SOURCES src/basic_update.cc src/dynamics_update.cc src/metropolis_update.cc src/metropolis_dynamics_update.cc)

add_library(system_update ${SYSTEM_UPDATE_SOURCES})

target_include_directories(system_update PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(system_update particle_system ode)
