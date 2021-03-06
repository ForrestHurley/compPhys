
#include "ode_solver.h"

ODESolver::ODESolver(bool flatten_input_state) :
  flatten_input_state(flatten_input_state) {}

ODESolver::ODESolver(
  ODEInterface* differential_equation,
  bool flatten_input_state) : 
  differential_equation(differential_equation),
  flatten_input_state(flatten_input_state) {}

void ODESolver::setDifferentialEquation(ODEInterface *differential_equation)
{
  this->differential_equation = differential_equation;  
}

void ODESolver::setState(const std::vector< std::vector<double> > &state)
{
  this->state = state;
}

void ODESolver::setState(const std::vector<double> &state)
{
  this->state.clear();
  this->state.push_back(state);
}

const std::vector< std::vector<double> >& ODESolver::getState() const
{
  return state;
}

void ODESolver::EvolveState(double total_time, int number_of_steps, double initial_time) 
{
  double step_size = total_time / number_of_steps;

  //Transform the input to be a nx1 vector of vectors
  //where the current derivs are just appended in series
  int particle_count, degrees, size;
  if (flatten_input_state)
  {
    //This breaks if the inputs are not of uniform size. That is fixable, but it would take work
    particle_count = state.size();
    degrees = state.at(0).size();
    size = particle_count * degrees;

    std::vector< std::vector<double> > temp_state = state;
    state.clear();
    state.reserve(size);

    for (int i = 0; i < size; i++)
    {
      state.push_back(
        std::vector<double>{
          temp_state.at(i % particle_count).at(i / particle_count)});
    }
  }

  for (unsigned int i = 0; i < number_of_steps; i++)
  {
    StepState(step_size, initial_time + step_size * i);
  }

  //Return input to original form
  if (flatten_input_state)
  {
    std::vector< std::vector<double> > temp_state = state;
    state.clear();

    for (int i = 0; i < particle_count; i++)
    {
      state.push_back(std::vector<double>());
    }

    for (int i = 0; i < size; i++)
    {
      state.at(i % particle_count).push_back(
        temp_state.at(i).at(0));
    }
  }
}

