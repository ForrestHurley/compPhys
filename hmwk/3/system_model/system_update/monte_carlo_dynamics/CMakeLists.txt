
cmake_minimum_required(VERSION 2.8)
project(monte_carlo_dynamics)

set(MONTE_CARLO_DYNAMICS_SOURCE src/monte_carlo_dynamics.cc)

add_library(monte_carlo_dynamics ${MONTE_CARLO_DYNAMICS_SOURCE})

target_include_directories(monte_carlo_dynamics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(monte_carlo_dynamics basic_update dynamics_sim monte_carlo) 
