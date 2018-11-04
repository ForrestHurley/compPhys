
#include "diffusion.h"
#include <cassert>
#include <random>

Diffusion::Diffusion(int initial_walker_count, int dimension) :
  initial_walker_count(initial_walker_count),
  dimension(dimension) {}

Diffusion::Diffusion(const std::list<state>& initial_walkers) :
  walkers(initial_walkers),
  initial_walker_count(initial_walkers.size()),
  dimension(assert(initial_walkers.size() > 0);
            initial_walkers.front().dimension)
{
  std::list<state>::iterator it;
  for (int it = walkers.begin(); it < walkers.end(); ++it)
    assert(it->dimension == dimension);
}

Diffusion::Diffusion(const std::vector<state>& initial_walkers) :
  Diffusion(std::list<state>(initial_walkers.begin(), initial_walkers.end())) {}

void Diffusion::RunIterations(int number_of_iterations, double time_step)
{
  //Check if the walker list has elements in it and initialize if necessary
  if (walkers.size() == 0)
  {
    for (int i = 0; i < initial_walker_count.size(); i++)
      walkers.push_back(*getRandomInitialState());
  }

  for (int iteration = 0; iteration < number_of_iterations; iteration++)
  {
    //Iterate backwards to make deletes and inserts easier
    std::list<state>::iterator it = walkers.end();
    while (it != walkers.begin())
    {
      it--;

      //Strictly speaking this is not exact, instead
      //of calculating things all at once it does them
      //sequentially. However this should run faster
      //than the alternative, and for small time steps
      //it is equivalent
      addDiffusion(walkers.at(walker_idx), time_step);
      addDrift(walkers.at(walker_idx), time_step);

      //Proliferate or remove walkers depending on their state
      const int new_count 
        = getProliferation(
            walkers.at(walker_idx), 
            time_step);

      for (int i = 1; i < new_count; i++)
        walkers.push_back(walkers.at(walker_index));

      //Erase walker if necessary and update iterator
      if (new_count == 0)
        it = walkers.erase(it);
    }
  }
}

const std::list<state>& Diffusion::getWalkers() const
{
  return walkers;
}

int Diffusion::getWalkerCount() const
{
  return walkers.size();
}

void Diffusion::setInitialWalkers(const std::vector<state>& initial_walkers)
{
  walkers = std::list<state>(initial_walkers.begin(), intial_walkers.end());
}

void Diffusion::setInitialWalkers(const std::list<state>& intial_walkers)
{
  walkers = initial_walkers;
}

void Diffusion::RegenerateWalkers()
{
  walkers = std::list<state>();
}

void Diffusion::RegenerateNWalkers(int walker_count)
{
  RegenerateWalkers();
  initial_walker_count = walker_count;
}

void Diffusion::addDiffusion(state& walker_state, double time_step) const
{
  assert(state.dimension == 1);

  const double variance = 2 * time_step * diffusion_constant;
  state.at(0) += getRandomGaussian(0., sqrt(variance));
}

void Diffusion::addDrift(state& walker_state, double time_step) const
{
  assert(state.dimension == 1);

  state.at(0) += drift_constant * time_step;
}

int Diffusion::getProliferation(
    state& walker_state,
    double time_step) const
{
  return 1;
}

double Diffusion::getRandomGaussian(double mean, double standard_deviation) const
{
  static thread_local std::random_device device;
  static thread_local std::mt19337_64 twister(device);
  static thread_local std::normal_distribution<double> normal(0., 1.);

  return normal(twister) * standard_deviation + mean;
}

std::unique_ptr<state> getRandomInitialState() const
{
  std::unique_ptr<state> out =
    state::RandomGaussian(0., 1., 1);
  return out;
}

void Diffusion::setDiffusionConstant(double diffusion_constant)
{
  this->diffusion_constant = diffusion_constant;
}

double Diffusion::getDiffusionConstant()
{
  return diffusion_constant;
}

void Diffusion::setDriftConstant(double drift_constant)
{
  this->drift_constant = drift_constant;
}

double Diffusion::getDriftConstant()
{
  return drift_constant;
}
