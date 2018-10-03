
cmake_minimum_required(VERSION 2.8)

project(monte_carlo)

set(MONTE_CARLO_SOURCES src/metropolis.cc src/metropolis_nvt.cc src/metropolis_npt.cc src/metropolis_uvt.cc)

add_library(monte_carlo ${MONTE_CARLO_SOURCES})

target_include_directories(monte_carlo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(monte_carlo basic_update)
