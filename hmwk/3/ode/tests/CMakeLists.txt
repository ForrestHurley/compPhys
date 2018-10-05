
cmake_minimum_required(VERSION 2.8)
project(ode_tests)

set(ODE_TESTS_SOURCES ode_solver_test.cc ode_interface_test.cc integ_verlet_test.cc integ_runge_kutta_test.cc)

add_executable(ode_tests ${ODE_TESTS_SOURCES})

target_include_directories(ode_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIRECTORY}/include)
target_link_libraries(ode_tests gmock_main ode)
target_compile_options(ode_tests PRIVATE -std=c++11)

add_test(NAME ode_tests COMMAND ode_tests)
