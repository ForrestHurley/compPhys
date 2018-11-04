
cmake_minimum_required(VERSION 2.8)

project(diffusion)

set(DIFFUSION_SOURCES
  src/state.cc src/diffusion.cc
  src/diffusion_monte_carlo.cc
  src/main.cc)

add_executable(diffusion ${DIFFUSION_SOURCES})
target_include_directories(diffusion PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
