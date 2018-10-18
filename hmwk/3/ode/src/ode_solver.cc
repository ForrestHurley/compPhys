
#include "ode_solver.h"

ODESolver::ODESolver() {}

ODESolver::ODESolver(ODEInterface* differential_equation) : differential_equation(differential_equation) {}

void ODESolver::setDifferentialEquation(ODEInterface *differential_equation)
{
  this->differential_equation = differential_equation;  
}

void ODESolver::StepState(std::vector<double> &state, double time_step, double time) 
{
  std::vector< std::vector<double> > manip_vect;
  manip_vect.push_back(state);

  StepState(manip_vect, time_step, time);

  state = manip_vect.at(0);
}

void ODESolver::EvolveState(std::vector< std::vector<double> > &state, double total_time, int number_of_steps, double initial_time) 
{
  double step_size = total_time / number_of_steps;

  for (unsigned int i = 0; i < number_of_steps; i++)
  {
    StepState(state, step_size, initial_time + step_size * i);
  }
}

void ODESolver::EvolveState(std::vector<double> &state, double total_time, int number_of_steps, double initial_time) 
{
  double step_size = total_time / number_of_steps;

  for (unsigned int i = 0; i < number_of_steps; i++)
  {
    StepState(state, step_size, initial_time + step_size * i);
  }
}

