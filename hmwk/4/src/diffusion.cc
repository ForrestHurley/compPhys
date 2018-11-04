
#include "diffusion.h"
#include <cassert>
#include <random>

Diffusion::Diffusion(int initial_walker_count, int dimension) :
  initial_walker_count(initial_walker_count),
  dimension(dimension) {}

Diffusion::Diffusion(const std::list<State>& initial_walkers) :
  walkers(initial_walkers),
  initial_walker_count(initial_walkers.size()),
  dimension((assert(initial_walkers.size() > 0),
            initial_walkers.front().dimension))
{
  std::list<State>::iterator it;
  for (it = walkers.begin(); it != walkers.end(); ++it)
    assert(it->dimension == dimension);
}

Diffusion::Diffusion(const std::vector<State>& initial_walkers) :
  Diffusion(std::list<State>(initial_walkers.begin(), initial_walkers.end())) {}

void Diffusion::RunIterations(int number_of_iterations, double time_step)
{
  //Check if the walker list has elements in it and initialize if necessary
  if (walkers.size() == 0)
  {
    for (int i = 0; i < initial_walker_count; i++)
      walkers.push_back(*getRandomInitialState());
  }

  for (int iteration = 0; iteration < number_of_iterations; iteration++)
  {
    //Iterate backwards to make deletes and inserts easier
    std::list<State>::iterator it = walkers.end();
    while (it != walkers.begin())
    {
      it--;

      //Strictly speaking this is not exact, instead
      //of calculating things all at once it does them
      //sequentially. However this should run faster
      //than the alternative, and for small time steps
      //it is equivalent
      addDiffusion(*it, time_step);
      addDrift(*it, time_step);

      //Proliferate or remove walkers depending on their state
      const int new_count 
        = getProliferation(
            *it, 
            time_step);

      for (int i = 1; i < new_count; i++)
        walkers.push_back(*it);

      //Erase walker if necessary and update iterator
      if (new_count == 0)
        it = walkers.erase(it);
      PostIteration();
    }
  }
}

const std::list<State>& Diffusion::getWalkers() const
{
  return walkers;
}

int Diffusion::getWalkerCount() const
{
  return walkers.size();
}

void Diffusion::setInitialWalkers(const std::vector<State>& initial_walkers)
{
  walkers = std::list<State>(initial_walkers.begin(), initial_walkers.end());
}

void Diffusion::setInitialWalkers(const std::list<State>& initial_walkers)
{
  walkers =
    std::list<State> (initial_walkers.begin(), initial_walkers.end());
}

void Diffusion::RegenerateWalkers()
{
  walkers = std::list<State>();
}

void Diffusion::RegenerateNWalkers(int walker_count)
{
  RegenerateWalkers();
  initial_walker_count = walker_count;
}

void Diffusion::addDiffusion(State& walker_state, double time_step) const
{
  assert(walker_state.dimension == 1);

  const double variance = 2 * time_step * diffusion_constant;
  walker_state.at(0) += getRandomGaussian(0., sqrt(variance));
}

void Diffusion::addDrift(State& walker_state, double time_step) const
{
  assert(walker_state.dimension == 1);

  walker_state.at(0) += drift_constant * time_step;
}

int Diffusion::getProliferation(
    State& walker_state,
    double time_step) const
{
  return 1;
}

double Diffusion::getRandomGaussian(double mean, double standard_deviation) const
{
  static thread_local std::random_device device;
  static thread_local std::mt19937_64 twister(device());
  static thread_local std::normal_distribution<double> normal(0., 1.);

  return normal(twister) * standard_deviation + mean;
}

std::unique_ptr<State> Diffusion::getRandomInitialState() const
{
  std::unique_ptr<State> out = 
    State::RandomGaussian(0., 1., dimension);
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
