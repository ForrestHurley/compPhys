#include "state.h"
#include "diffusion.h"
#include "diffusion_monte_carlo.h"
#include <iostream>
#include <fstream>
#include <random>
#include <cassert>

class NonConstantDriftDiffusion : public Diffusion
{
protected:
  virtual void addDrift(State& walker_state, double time_step) const override
  {
    assert(walker_state.dimension == 1);

    walker_state.at(0) -= walker_state.at(0) * time_step;
  }

public:
  explicit NonConstantDriftDiffusion(const std::vector<State>& initial_walkers) :
    Diffusion(initial_walkers) {}
};

void DMC()
{
  std::cout << "Starting DMC" << std::endl;

  int initial_iterations = 10000;
  double iteration_time_step = 0.00001;

  std::cout << "Calculated Energies:" << std::endl;
  for (int i = 0; i < 200; i++)
  {
    //Proton count, electron count, guess, dimension, walker count
    DiffusionMonteCarlo simulator
      = DiffusionMonteCarlo(2, 2, -2.9, 3, 1000);
    
    //Burn in period
    //Iterations, time step
    simulator.RunIterations(initial_iterations / 5., iteration_time_step * 1000);
    simulator.RunIterations(initial_iterations / 5., iteration_time_step * 100);
    simulator.RunIterations(initial_iterations / 5., iteration_time_step * 10);
    simulator.RunIterations(initial_iterations / 2.5, iteration_time_step * 1);

    int count = simulator.getPastCalculatedEnergies().size();
    double energy = simulator.getPastCalculatedEnergies().at(count - 1);

    std::cout << energy << std::endl;
  }

  std::cout << "Finished simulating atom" << std::endl;
}

void Diffusion()
{
  //std::cout << "Starting diffusion calculation" << std::endl;

  //Generate distribution of initial states
  std::vector<State> initial_walkers;

  std::random_device device;
  std::mt19937_64 twister(device());
  std::normal_distribution<double> normal(-3., 1.);

  //std::cout << "Initializing walkers" << std::endl;
  const int walker_count = 1000000;
  initial_walkers.reserve(walker_count);
  for (int i = 0; i < walker_count; i++)
  {
    initial_walkers.push_back(
        State(std::vector<double>{normal(device)}));
  }

  //std::cout << "Running calculation" << std::endl;
  //Initialize diffusion class
  NonConstantDriftDiffusion diffusor(initial_walkers);

  //Number of iterations, time step, verbose
  diffusor.RunIterations(10000,0.01,true);

  std::cout << "Outputing results" << std::endl;

  std::ofstream out_file("diffusion.csv");
  //Output final walker states
  const std::list<State>& final_walkers =
    diffusor.getWalkers();
  for (const State& state : final_walkers)
    out_file << state.at(0) << std::endl;
  out_file.close();
}

int main()
{
  DMC();
  //Diffusion(); 
}
