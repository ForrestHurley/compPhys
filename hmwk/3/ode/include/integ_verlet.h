#ifndef INTEG_VERLET_H
#define INTEG_VERLET_H

#include "ode_solver.h"
#include "ode_interface.h"
#include <vector>

class VerletIntegrator : public ODESolver
{
public:
  VerletIntegrator();
  VerletIntegrator(ODEInterface *differential_equation);

  virtual void StepState(std::vector<double> &state, double time_step) override;
};

#endif
