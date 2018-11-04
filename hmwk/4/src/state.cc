
#include "state.h"
#include <random>
#include <cassert>

State::State(int dimension) :
  dimension(dimension)
{
  internal_state = std::vector<double>(dimension, 0.);
}

State::State(const std::vector<double>& initial_state) :
  dimension(initial_state.size())
{
  internal_state = initial_state;
} 

std::unique_ptr<State> State::RandomGaussian(
    double mean, double standard_deviation, int dimension)
{
  std::unique_ptr<State> out (new State(dimension));

  static thread_local std::random_device device;
  static thread_local std::mt19937_64 twister(device());
  static thread_local std::normal_distribution<double> normal(0., 1.);

  for (int i = 0; i < dimension; i++)
    out->at(i) = normal(twister) * standard_deviation + mean;

  return out;
}

double& State::at(int i)
{
  return internal_state.at(i);
}

const double& State::at(int i) const
{
  return internal_state.at(i);
}

void State::setElement(int i, double value)
{
  internal_state.at(i) = value;
}

double State::getElement(int i) const
{
  return internal_state.at(i);
}

double State::getDistanceSquared(const State& other) const
{
  assert(other.dimension == dimension);

  double squared = 0.;
  for (int i = 0; i < dimension; i++)
  {
    const double this_val = internal_state.at(i);
    const double other_val = other.internal_state.at(i);
    squared += (this_val - other_val) * (this_val - other_val);
  }
  return squared;
}

double State::getDistance(const State& other) const
{
  return sqrt(getDistanceSquared(other));
}

double State::getDistanceFromOrigin() const
{
  double squared = 0.;
  for (int i = 0; i < dimension; i++)
  {
    const double this_val = internal_state.at(i);
    squared += this_val * this_val;
  }
  return sqrt(squared);
}