
cmake_minimum_required(VERSION 2.8)
project(dynamics_sim)

set(DYNAMICS_SIM_SOURCES src/dynamic_update.cc)

add_library(dynamics_sim ${DYNAMICS_SIM_SOURCES})

target_link_libraries(dynamics_sim basic_update)
