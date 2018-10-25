
cmake_minimum_required(VERSION 2.8)
project(ode)

add_subdirectory(tests)

set( ODE_SOURCES src/ode_interface.cc src/ode_solver.cc src/integ_runge_kutta.cc src/integ_verlet.cc )

add_library(ode ${ODE_SOURCES})
target_include_directories(ode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ode metric_space)
