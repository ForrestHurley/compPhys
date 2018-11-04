
#include "diffusion_monte_carlo.h"
#include <math.h>
#include <cassert>
#include <random>

DiffusionMonteCarlo::DiffusionMonteCarlo(
    double nucleus_count,
    int electron_count,
    double energy_guess,
    int dimension,
    int initial_walker_count) :
  nucleus_count(nucleus_count),
  electron_count(electron_count),
  goal_walker_count(initial_walker_count),
  energy_guess(energy_guess),
  energy_t(energy_guess),
  geometric_dimension(dimension),
  Diffusion(initial_walker_count, electron_count * dimension + 1) {}

#include <iostream>
double DiffusionMonteCarlo::getCalculatedEnergy() const
{
  double total_energy = 0.;

  std::list<State>::const_iterator it = getWalkers().begin();
  for (; it != getWalkers().end(); ++it)
  {
    total_energy += it->at(electron_count * geometric_dimension);
  }

  return total_energy / getWalkerCount();
}

void DiffusionMonteCarlo::CalculatePotential(State& walker_state) const
{
  double energy = 0.;

  for (int i = 0; i < electron_count; i++)
  {
    double distance_squared = 0.;
    for (int j = 0; j < geometric_dimension; j++)
      distance_squared += 
        walker_state.getElement(geometric_dimension * i + j) *
        walker_state.getElement(geometric_dimension * i + j);
    
    const double recip_dist = 1. / sqrt(distance_squared);
    energy -= recip_dist * nucleus_count;
  }

  for (int i = 0; i < electron_count; i++)
  {
    for (int j = i + 1; j < electron_count; j++)
    {
      double distance_squared = 0.;
      for (int k = 0; k < geometric_dimension; k++)
      {
        const double displacement =
          walker_state.getElement(geometric_dimension * i + k) -
          walker_state.getElement(geometric_dimension * j + k);

        distance_squared += displacement * displacement;
      }

      const double recip_dist = 1. / sqrt(distance_squared);
      energy += recip_dist;
    }
  }

  walker_state.setElement(electron_count * geometric_dimension, energy);
}

void DiffusionMonteCarlo::addDiffusion(State& walker_state, double time_step) const
{
  assert(walker_state.dimension == electron_count * geometric_dimension + 1);

  const double standard_deviation = sqrt(time_step);
  for (int i = 0; i < dimension; i++)
    walker_state.at(i) += getRandomGaussian(0., standard_deviation);
}

void DiffusionMonteCarlo::addDrift(State& walker_state, double time_step) const {}

int DiffusionMonteCarlo::getProliferation(State& walker_state, double time_step) const
{
  assert(walker_state.dimension == electron_count * geometric_dimension + 1);

  const double old_potential = walker_state.at(electron_count * geometric_dimension);
  CalculatePotential(walker_state);
  const double new_potential = walker_state.at(electron_count * geometric_dimension);

  static thread_local std::random_device device;
  static thread_local std::mt19937_64 twister(device());
  static thread_local std::uniform_real_distribution<double> uniform(0., 1.);

  const double energies =
    old_potential + new_potential - 2 * energy_t;
  const double exponent = - time_step * energies / 2;
  const int new_count =
    floor(exp(exponent) + uniform(twister));

  return new_count;
}

void DiffusionMonteCarlo::PostIteration()
{
  energy_t =
    energy_guess - log((double)getWalkerCount() / goal_walker_count);
}

