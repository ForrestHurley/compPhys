
cmake_minimum_required(VERSION 2.8)
project(data_logging)

set(DATA_LOGGING_SOURCES src/data_logger.cc src/displacement_logger.cc src/energy_logger.cc
  src/pressure_logger.cc src/r_squared_logger.cc
  src/state_logger.cc src/temperature_logger.cc)

add_library(data_logging ${DATA_LOGGING_SOURCES})

target_include_directories(data_logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(data_logging particle_system)
