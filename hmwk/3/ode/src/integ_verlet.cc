
#include "integ_verlet.h"
#include "integ_runge_kutta.h"

VerletIntegrator::VerletIntegrator() : initial_solver(*new RungeKuttaIntegrator()){}

VerletIntegrator::VerletIntegrator(ODEInterface *differential_equation) : 
  ODESolver(differential_equation), 
  initial_solver(*new RungeKuttaIntegrator(differential_equation)) {}

VerletIntegrator::VerletIntegrator(
  ODEInterface *differential_equation, ODESolver& initial_solver) : 
  ODESolver(differential_equation), 
  initial_solver(initial_solver) {}

void VerletIntegrator::InitializeFirstState(std::vector<double> &state,
  double time_step, double initial_time)
{
  std::vector< std::vector<double> > manip_vect;
  manip_vect.push_back(state);

  InitializeFirstState(manip_vect, time_step, initial_time);
}

void VerletIntegrator::InitializeFirstState(std::vector< std::vector<double> > &state,
  double time_step, double initial_time)
{
  initial_solver.setDifferentialEquation(differential_equation);

  previous_state = state;
  initial_solver.EvolveState(state, time_step, 1, initial_time);
}

//TODO: Modify to work with flat torus spaces
void VerletIntegrator::StepState(std::vector< std::vector<double> > &state, double time_step, double time) 
{
  std::vector<double> acceleration =
    differential_equation->CalculateHighestDerivative(state, time);

  std::vector< std::vector<double> > out;
  out.reserve(state.size());

  for (unsigned int i = 0; i < state.size(); i++)
  {
    std::vector<double> out_row;

    //position calculation
    out_row.push_back(
      2 * state.at(i).at(0) - previous_state.at(i).at(0) +
      acceleration.at(i) * time_step * time_step);

    //velocity calculation
    out_row.push_back(
      (out_row.at(0) - previous_state.at(i).at(0)) / ( 2 * time_step ));

    out.push_back(out_row);
  }

  previous_state = state;
  state = out;
}

void VerletIntegrator::EvolveState(std::vector< std::vector<double> > &state, double total_time, int number_of_steps, double initial_time) 
{
  double step_size = total_time / number_of_steps;

  InitializeFirstState(state, step_size, initial_time);
  ODESolver::EvolveState(state,
    total_time - step_size, number_of_steps - 1, initial_time + step_size);
}

void VerletIntegrator::EvolveState(std::vector<double> &state, double total_time, int number_of_steps, double initial_time) 
{
  double step_size = total_time / number_of_steps;

  InitializeFirstState(state, step_size, initial_time);
  ODESolver::EvolveState(state,
    total_time - step_size, number_of_steps - 1, initial_time + step_size);
}

