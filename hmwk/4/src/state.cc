
#include "state.h"

State::State(int dimension) :
  dimension(dimension)
{
  internal_state = std::vector<double>(dimension);
}

State::State(const std::vector<double>& initial_state) :
  dimension(initial_state.size())
{
  internal_state = initial_state;
} 

static std::unique_ptr<state> State::RandomGaussian(
    double mean, double standard_deviation, int dimension)
{
  std::unique_ptr<state>
    = new state(dimension);

  static thread_local std::random_device device;
  static thread_local std::mt19337_64 twister(device);
  static thread_local std::normal_distribution<double> normal(0., 1.);

  for (int i = 0; i < dimension; i++)
    state.at(i) = normal(twister) * standard_deviation + mean;
}

double& State::at(int i)
{
  return internal_state.at(i);
}

const double& State::at(int i) const
{
  return internal_state.at(i);
}
