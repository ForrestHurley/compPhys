
#include "integ_runge_kutta.h"

RungeKuttaIntegrator::RungeKuttaIntegrator(const ODEInterface &differential_equation) : 
  ODESolver(differential_equation) {}

void RungeKuttaIntegrator::StepState(std::vector<double> &state, double time_step) {};
