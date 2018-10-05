#ifndef ODE_SOLVER_TEST_H
#define ODE_SOLVER_TEST_H

#include "ode_solver.h"
#include "ode_interface_test.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MockODESolver : public ODESolver
{
public:
  MockODESolver(int degree = 2) : ODESolver(MockODEInterface(degree)) {};
  MockODESolver(ODEInterface &differential_equation) : ODESolver(differential_equation) {};

  using ODESolver::StepState;
  MOCK_METHOD2(StepState, void (std::vector<double> &state, double time_step) );
};

#endif
