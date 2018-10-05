
#include "ode_solver.h"

ODESolver::ODESolver(const ODEInterface &differential_equation) : differential_equation(differential_equation) {};

void ODESolver::StepState(std::vector<double> &state, double time_step) {}

void ODESolver::EvolveState(std::vector< std::vector<double> > &state, double total_time, int number_of_steps) {}

void ODESolver::EvolveState(std::vector<double> &state, double total_time, int number_of_steps) {}
