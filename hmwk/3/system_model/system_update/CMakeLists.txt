
cmake_minimum_required(VERSION 2.8)
project(system_update)

add_subdirectory(basic_update)
add_subdirectory(dynamics_sim)
add_subdirectory(monte_carlo)
add_subdirectory(monte_carlo_dynamics)

add_library(system_update INTERFACE)

target_link_libraries(system_update INTERFACE basic_update dynamics_sim monte_carlo monte_carlo_dynamics)
