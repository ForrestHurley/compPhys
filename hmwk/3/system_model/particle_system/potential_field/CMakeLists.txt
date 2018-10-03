
cmake_minimum_required(VERSION 2.8)
project(potential_field)

set(POTENTIAL_FIELD_SOURCES src/potential_field.cc)

add_library(potential_field ${POTENTIAL_FIELD_SOURCES})

target_include_directories(potential_field PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
