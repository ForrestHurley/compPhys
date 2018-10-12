#ifndef ODE_SOLVER_TEST_H
#define ODE_SOLVER_TEST_H

#include "ode_solver.h"
#include "ode_interface_test.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MockODESolver : public ODESolver
{
  ODEInterface *ode_function;
public:
  MockODESolver(int degree = 2) : ode_function(new MockODEInterface(degree)), ODESolver(ode_function) {};
  MockODESolver(ODEInterface *differential_equation) : 
    ode_function(differential_equation), ODESolver(ode_function) {};

  using ODESolver::StepState;
  MOCK_METHOD2(StepState, void (std::vector<double> &state, double time_step) );
};

#endif
