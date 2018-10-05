
#include "integ_verlet.h"

VerletIntegrator::VerletIntegrator(const ODEInterface &differential_equation) : ODESolver(differential_equation) {}

void VerletIntegrator::StepState(std::vector<double> &state, double time_step) {}
