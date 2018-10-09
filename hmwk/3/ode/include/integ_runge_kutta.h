#ifndef INTEG_RUNGE_KUTTA_H
#define INTEG_RUNGE_KUTTA_H

#include "ode_solver.h"
#include "ode_interface.h"
#include <vector>

class RungeKuttaIntegrator : public ODESolver
{
public:
  RungeKuttaIntegrator();
  RungeKuttaIntegrator(ODEInterface *differential_equation);

  virtual void StepState(std::vector<double> &state, double time_step) override;
};

#endif
