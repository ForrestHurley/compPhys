
cmake_minimum_required(VERSION 2.8)
project(system_model)

add_subdirectory(particle_system)
add_subdirectory(system_update)

add_library(system_model INTERFACE)
target_link_libraries(system_model INTERFACE particle_system system_update)
