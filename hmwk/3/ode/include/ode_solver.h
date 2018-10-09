#ifndef ODE_SOLVER_H
#define ODE_SOLVER_H

#include <vector>
#include "ode_interface.h"

class ODESolver
{
protected:
  ODEInterface *differential_equation;

public:
  ODESolver();
  ODESolver(ODEInterface *differential_equation); 

  void setDifferentialEquation(ODEInterface *differential_equation);

  virtual void StepState(std::vector< std::vector<double> > &state, double time_step);
  virtual void StepState(std::vector<double> &state, double time_step) = 0;

  virtual void EvolveState(std::vector< std::vector<double> > &state, double total_time, int number_of_steps);
  virtual void EvolveState(std::vector<double> &state, double total_time, int number_of_steps);
};

#endif
