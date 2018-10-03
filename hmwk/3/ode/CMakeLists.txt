
project(ode)

set( ODE_SOURCES src/state_integrator.cc src/integ_runge_kutta.cc src/integ_verlet.cc )

add_library(ode ${ODE_SOURCES})
